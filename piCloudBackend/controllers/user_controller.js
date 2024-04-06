const user = require("../models/user_model");
const device = require("../models/device_model");
const functionality = require("../models/functionality_model");
const config = require("../models/config_model");


exports.getUsers = async (req, res) => {
    try {
        const users = await user.find();

        res.status(200).json({
            success: true,
            data: users,
        });
    } catch (err) {
        res.status(500).json({
            success: false,
            message: err.message,
        });
    }
};

exports.createDevice = async (req, res) => {
    try {
        const { userid, device_id, functionality_ids, route_names, routes, config_ids, config_names, config_values } = req.body;

        const newUser = await user.create({
            userid,
            device_ids: [device_id],
        });

        await newUser.save();

        const newDevice = await device.create({
            device_id,
            functionality_ids: [functionality_ids],
            config_ids: [config_ids],
        });

        await newDevice.save();

        for (var i = 0; i < functionality_ids.length; i++) {
            const functionalityModel = await functionality.create({
                functionality_id: functionality_ids[i],
                routeName: route_names[i],
                route: routes[i],
            });

            await functionalityModel.save();
        }

        for (var i = 0; i < config_ids.length; i++) {
            const configModel = await config.create({
                config_id: config_ids[i],
                config_name: config_names[i],
                config_value: config_values[i],
            });

            await configModel.save();
        }

        res.status(201).json({
            success: true,
            message: "Device created successfully",
        });

    } catch (err) {
        throw err;
        res.status(500).json({
            success: false,
            message: err.message,
        });
    }
}

exports.addDevice = async (req, res) => {
    try {
        const { userid, device_id, functionality_ids, route_names, routes, config_ids, config_names, config_values } = req.body;

        const userDevice = await user.findOne({ userid });

        if (!userDevice) {

            res.status(404).json({
                success: false,
                message: "User not found",
            });

        }

        userDevice.device_ids.push(device_id);

        await userDevice.save();

        const newDevice = await device.create({
            device_id,
            functionality_ids,
            config_ids,
        });

        await newDevice.save();

        const functionalityModel = await functionality.create({
            functionality_id: functionality_ids,
            routeName: route_names,
            route: routes,
        });

        await functionalityModel.save();

        const configModel = await config.create({
            config_id: config_ids,
            config_name: config_names,
            config_value: config_values,
        });

        await configModel.save();

        res.status(201).json({
            success: true,
            message: "Device added successfully",
        });

    } catch (err) {
        res.status(500).json({
            success: false,
            message: err.message,
        });
    }
};

exports.getUserDevices = async (req, res) => {
    try {
        const userid = req.params.id;

        const userDevices = await user.findOne({ userid }).populate("device_ids").populate("functionalities_ids", "config_ids").exec();

        res.status(200).json({
            success: true,
            data: userDevices,
        });
    } catch (err) {
        throw err;
        res.status(500).json({
            success: false,
            message: err.message,
        });
    }
}

