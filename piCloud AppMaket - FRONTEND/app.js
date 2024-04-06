HVHAuth = new auth("ad9sza4lsl1Idh6sosfreDr7ryyakocvg6H62pd7o51il850")

async function user(){
    let data = await this.HVHAuth.getUser()
    return data
}


window.onload = async function(){
    let mu = await user()
    if(mu == null){
        location.href="auth/"
    }else{
        console.log(mu)
    }
}