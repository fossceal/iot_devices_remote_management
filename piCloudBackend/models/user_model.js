const mongoose = require("mongoose");

const userSchema = new mongoose.Schema({
    userid: {
        type: String,
        required: true,
        unique: true,
    },
    device_ids: {
        type: Array,
        required: false,
    }
});

module.exports = mongoose.model("User", userSchema);