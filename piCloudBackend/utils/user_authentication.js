// HVH Auth Library

const axios = require("axios");


class auth {
    api_route = "https://auth-hvh.b4a.app"
    api_key;
    user_key = null;
    constructor(key) {
        this.api_key = key

    }


    async getUser() {
        try {
            
            if (this.user_key == null) {
                return null
            }
            let response = await axios.get(this.api_route + `/getUser/${this.api_key}/${this.user_key}`, { withCredentials: true })
            if (response.data.status == "success") {
                return response.data.data.user
            } else {
                return null
            }
        } catch (error) {
            console.error("Error fetching User data:", error);
            return null;
        }
    }

    async requestKey() {


        try {

            let response = await axios.get(this.api_route + `/requestKey/${this.api_key}`, { withCredentials: true })
            if (response.data.status == "success") {
                localStorage.setItem("auth", response.data.key)
                this.user_key = response.data.key
                return {
                    status: "success",
                    msg: "Key Set"
                }
            }
            else {
                return {
                    status: "error",
                    msg: "err generating key",
                    error: response.data
                }
            }

        } catch (error) {
            console.error("Error requesting KEY:", error);
            return null;
        }
    }

    async requestLoginURL() {
        try {

            let response = await axios.get(this.api_route + `/requestURL/${this.api_key}/${this.user_key}`, { withCredentials: true })
            if (response.data.status == "success") {
                return {
                    status: "success",
                    url: response.data.url
                }
            } else {
                return {
                    status: "error",
                    msg: "err requesting login url",
                    error: response.data
                }
            }

        } catch (error) {
            console.error("Error requesting Login URL :", error);
            return null;
        }
    }



    async testReq() {
        let response = await fetch(this.api_route + "/test", {
            method: 'GET', credentials: 'include', CORS: 'no-cors',
            headers: {
                'Content-Type': 'application/json'
            },
        });

        return response.data
    }



}

module.exports = auth;
