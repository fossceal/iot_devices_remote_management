const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
require("dotenv").config();
require("./configs/db");
const { isAuthenticatedUser } = require("./middlewares/auth");

const app = express();

app.use(express.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use(cors());

const userRouter = require("./routes/user_routes");

app.use("/api/v1", userRouter);

app.get("/", (req, res) => {
  isAuthenticatedUser();
  res.end("Hello from pi-cloud-server");
});

app.listen(process.env.PORT, () => {
  console.log("Server is running on port " + process.env.PORT + "...")
});