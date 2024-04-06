var components = document.getElementsByClassName("componentList")[0].children;
const bodyRect = document.body.getBoundingClientRect();

function geneePlaceBlocks(){
    var tem = `
        <div class="placeBLXK" id="%%" style="grid-row:#$/@#;grid-column:#%/^&;color:white">
        THEMPI_PP
        </div>
        `

        for(var i=1;i<=100;i++){
            var temp = tem.replace("%%",i);
            temp = temp.replace("#$",);
            temp = temp.replace("#%",);
            temp = temp.replace("THEMPI_PP",i);
            document.getElementsByClassName("screen")[0].innerHTML+=temp;
        }
}


var componentRegistry = {

}
for (let i = 0; i < components.length; i++) {
    componentRegistry[components[i].id] = components[i];
}


function cursorPosition(event) {
    console.log(event.clientX, event.clientY);
}

// const divRect =components[0].getBoundingClientRect();

// const divPosition = {
//   top: divRect.top - bodyRect.top,
//   left: divRect.left - bodyRect.left,
// };



