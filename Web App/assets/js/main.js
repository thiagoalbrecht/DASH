document.addEventListener('DOMContentLoaded', function() {

	var tooltipTriggerList = [].slice.call(document.querySelectorAll('[data-bss-tooltip]'));
	var tooltipList = tooltipTriggerList.map(function (tooltipTriggerEl) {
	  return new bootstrap.Tooltip(tooltipTriggerEl);
	})
}, false);

const notyf = new Notyf({
    duration: 1500,
    ripple: false
});
var logs = false;
InitWebSocket();
function InitWebSocket() {
    try {
        ws = new WebSocket('ws://dash.onthewifi.com:81');
    } catch (err) {
        //notyf.error(err.message);
        wsLoaded(false);
    }
    ws.onmessage = function (evt) {
        JSONobj = JSON.parse(evt.data);
        if (JSONobj.readyState) {
            //notyf.success('Connected!');
            wsLoaded(true);
        }
    if (logs) notyf.success(JSON.stringify(JSONobj));
    }
    ws.addEventListener('close', function (event) {
        //notyf.error('Disconnected.');
        document.getElementById("robot-error").classList.remove("d-none");
        document.getElementById("controls").classList.add("d-none");
    });
    ws.addEventListener('error', function (event) {
        //notyf.error('Connection failed.');
        document.getElementById("robot-error").classList.remove("d-none");
        document.getElementById("controls").classList.add("d-none");
    });
}
//-------------------------------------------------------------

function wsLoaded(state) {
    if (state) {
        document.getElementById("robot-loading").classList.add("d-none");
        document.getElementById("controls").classList.remove("d-none");
        document.getElementById("robot-error").classList.add("d-none");
    }
    else {
        document.getElementById("robot-loading").classList.remove("d-none");
        document.getElementById("controls").classList.add("d-none");
    }
}
/*
function cameraViewLoaded() {
    document.getElementById("cam-placeholder").classList.add("d-none");
    document.getElementById("cam-loading").classList.add("d-none");
    document.getElementById("stream").classList.remove("d-none");
}
*/

function sendDashCommand(direction) {
    switch (direction) {
        case 'left':
            ws.send("m=1");
            break;
        case 'right':
            ws.send("m=-1");
            break;
        case 'stop':
        default:
            ws.send("m=0");
            break;
    }
}

let keyPressed = false;
let eventKey;
window.addEventListener("keydown", function (event) {
    if (event.defaultPrevented) {
        return; // Do nothing if the event was already processed
    }

    executeKey(event.key);

    // Cancel the default action to avoid it being handled twice
    event.preventDefault();
}, true);

window.addEventListener("keyup", function (event) {
    keyPressed = false;
    if(event.key == "ArrowLeft" || event.key == "Left" || event.key == "ArrowRight" || event.key == "Right") sendDashCommand("stop");
})

function stopMovement() {
    keyPressed = false;
    sendDashCommand("stop");
}

function executeKey(key) {
    if (!keyPressed) {
        keyPressed = true;
        switch (key) {
            case "Left": // IE/Edge specific value
            case "ArrowLeft":
                sendDashCommand("left");
                break;
            case "Right": // IE/Edge specific value
            case "ArrowRight":
                sendDashCommand("right");
                break;
            case "/":
                logs = !logs;
                if (logs) notyf.success("Logs turned on")
                else notyf.error("Logs turned off");
                break;
            case "1":
            case "2":
            case "3":
            case "4":
                ws.send("btn="+key);
                break;
            case "T":
            case "t":
                ws.send("btn=0");
                break;
            default:
                return; // Quit when this doesn't handle the key event.   
        }
    }
}

/*
const notyf = new Notyf({
    ripple: false,
    position: {
        x: 'right',
        y: 'top',
    },
    duration: 5000,
    dismissible: true
});
*/


let highQual = false;

function switchQuality(){
    if (!highQual){
        fetch('http://dashcam.onthewifi.com/control?var=quality&val=13',{ method: 'GET' })
        fetch('http://dashcam.onthewifi.com/control?var=framesize&val=10',{ method: 'GET' })
        document.getElementById("qualitytoggle").classList.add("btn-success");
        document.getElementById("qualitytoggle").classList.remove("btn-secondary");
    } else{
        fetch('http://dashcam.onthewifi.com/control?var=quality&val=34',{ method: 'GET' })
        fetch('http://dashcam.onthewifi.com/control?var=framesize&val=8',{ method: 'GET' }) 
        document.getElementById("qualitytoggle").classList.remove("btn-success");
        document.getElementById("qualitytoggle").classList.add("btn-secondary");
    }
    highQual = !highQual;
}


// element that will be wrapped

var el = document.getElementById("stream");
	
var wrapper = document.createElement("div");

wrapper.classList.add("d-flex", "justify-content-end", "align-items-end", "stream-wrapper");
	
el.parentNode.insertBefore(wrapper, el);
	
wrapper.appendChild(el);

let streamElement = document.getElementById("stream");

streamElement.insertAdjacentHTML("afterend", '<button class="btn btn-secondary btn-sm position-absolute m-1" data-bs-toggle="tooltip" data-bss-tooltip="" data-bs-placement="bottom" id="qualitytoggle" type="button" title="" onclick="switchQuality()" data-bs-original-title="Toggle High Quality" aria-label="Toggle High Quality"><i class="fa fa-eye"></i></button>')
