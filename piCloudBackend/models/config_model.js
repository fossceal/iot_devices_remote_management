const mongoose = require("mongoose");

const configSchema = new mongoose.Schema({
    config_id: {
        type: String,
        required: true,
        unique: true,
    },
    config_name: {
        type: String,
        required: true,
    },
    config_value: {
        type: String,
        required: true,
    }
});

module.exports = mongoose.model("Config", configSchema);