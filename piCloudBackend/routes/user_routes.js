const userRouter = require("express").Router();

const { getUserDevices, getUsers, addDevice, createDevice } = require("../controllers/user_controller");

userRouter.get("/users", getUsers);

userRouter.get("/devices/:id", getUserDevices);

userRouter.post("/addDevice", addDevice);

userRouter.post("/createDevice", createDevice);

module.exports = userRouter;