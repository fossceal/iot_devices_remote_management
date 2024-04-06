const auth = require("../utils/user_authentication");

exports.isAuthenticatedUser = async (req, res, next) => {
    // const { token } = req.header;

    // if (!token) {
    //     return res.status(401).json({
    //         success: false,
    //         message: "Login to access this resource",
    //     });
    // }

    const result = new auth(process.env.API_KEY);

    result.user_key = "up1jchH3hr44za983wfr39iw1mhaferaue3cjw4ktues0ip8";

    const user = await result.getUser();

    if (!user) {
        return res.status(401).json({
            success: false,
            message: "Login to access this resource",
        });
    }

    req.user = user;

    next();
};

// // Admin Roles
// exports.authorizeRoles = (...roles) => {
//     return (req, res, next) => {
//         if (!roles.includes(req.user.role)) {
//             return res.status(500).json({
//                 success: false,
//                 message: "You are not allowed to access this resource",
//             });
//         };
//         next();
//     }
// }