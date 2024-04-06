const mongoose = require("mongoose");

const functionalitySchema = new mongoose.Schema({
    functionality_id: {
        type: String,
        required: true,
        unique: true,
    },
    routeName: {
        type: String,
        required: true,
    },
    route: {
        type: String,
        required: true,
    }
});

module.exports = mongoose.model("Functionality", functionalitySchema);