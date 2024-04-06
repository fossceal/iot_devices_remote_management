const { config } = require("dotenv");
const mongoose = require("mongoose");

const deviceSchema = new mongoose.Schema({
    device_id: {
        type: String,
        required: true,
        unique: true,
    },
    functionalities_ids: {
        type: Array,
        required: false,
    },
    config_ids: {
        type: Array,
        required: false,
    }
});

module.exports = mongoose.model("Device", deviceSchema);