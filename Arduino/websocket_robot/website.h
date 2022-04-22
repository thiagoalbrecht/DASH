const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <title>DashLabs</title>
    <link rel="stylesheet" href="assets/bootstrap/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&amp;display=swap">
    <link rel="stylesheet" href="assets/css/Disket%20Mono.css">
    <link rel="stylesheet" href="assets/fonts/fontawesome-all.min.css">
    <link rel="stylesheet" href="assets/fonts/font-awesome.min.css">
    <link rel="stylesheet" href="assets/fonts/fontawesome5-overrides.min.css">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/notyf@3/notyf.min.css">
    <link rel="stylesheet" href="assets/css/styles.css">
</head>

<body style="--bs-primary: #83b71a;--bs-primary-rgb: 131,183,26;font-family: 'Disket Mono';">
    <nav class="navbar navbar-dark navbar-expand-md">
        <div class="container-fluid"><a class="navbar-brand ms-3" href="#" style="font-size: 30px;"><strong>D.-A.-S.-H</strong><span class="ms-3" style="font-size: 20px;color: var(--bs-primary);">\labs</span><br></a><button data-bs-toggle="collapse" class="navbar-toggler" data-bs-target="#navcol-1"><span class="visually-hidden">Toggle navigation</span><span class="navbar-toggler-icon"></span></button>
            <div class="collapse navbar-collapse d-md-flex justify-content-md-end" id="navcol-1" style="font-weight: bold;font-size: 18px;">
                <ul class="navbar-nav">
                    <li class="nav-item"><a class="nav-link active ms-3" href="#" style="font-weight: bold;">Home</a></li>
                    <li class="nav-item"><a class="nav-link" href="https://portfolio.cr.utwente.nl/student/sinkovichana/AboutDash.html">About</a></li>
                </ul>
            </div>
        </div>
    </nav>
    <div class="container">
        <div class="row">
            <div class="col-md-12 col-lg-5 col-xl-4 col-xxl-5 d-flex justify-content-center align-items-center">
                <div class="card d-none" id="controls" style="background: var(--bs-body-bg);">
                    <div class="card-body text-center">
                        <h6 class="text-center card-title border-bottom">Movement</h6><button class="moveButton" type="button" onmousedown="executeKey(&quot;Left&quot;)" onmouseup="stopMovement()">&lt; Left</button><button class="moveButton" type="button" onmousedown="executeKey(&quot;Right&quot;)" onmouseup="stopMovement()">Right &gt;</button>
                        <p class="text-white" style="font-size: 12px;">press ← → keys to move the robot</p>
                        <h6 class="text-center card-title border-bottom mt-5">Buttons</h6><button id="btn1" class="moveButton" type="button" onclick="ws.send(&#39;btn=1&#39;)">1</button><button id="btn2" class="moveButton" type="button" onclick="ws.send(&#39;btn=2&#39;)">2</button><button id="btn3" class="moveButton" type="button" onclick="ws.send(&#39;btn=3&#39;)">3</button><button id="btn4" class="moveButton" type="button" onclick="ws.send(&#39;btn=4&#39;)">4</button>
                    </div>
                </div>
                <div class="text-center" id="robot-loading"><span class="spinner-border" role="status"></span>
                    <p>Connecting</p>
                </div>
                <div class="text-center text-danger d-none" id="robot-error"><i class="far fa-times-circle" style="font-size: 32px;"></i>
                    <p>Disconnected</p><button class="btn btn-outline-success btn-sm" type="button" onclick="window.location.reload();">Retry</button>
                </div>
            </div>
            <div class="col text-center d-flex justify-content-center align-items-center">
                <div class="d-flex justify-content-end align-items-end"><img class="rounded" id="stream" src="http://dashcam.onthewifi.com:81/stream" style="max-width: 640px;width: 100%;height: auto;" width="640" height="480" onerror="this.onerror=null;this.src=&#39;streaming_error.png&#39;;" crossorigin=""><button class="btn btn-secondary btn-sm position-absolute m-1" data-bs-toggle="tooltip" data-bss-tooltip="" data-bs-placement="bottom" id="qualitytoggle" type="button" title="Turn on High Quality" onclick="switchQuality()"><i class="fa fa-eye"></i></button></div>
            </div>
        </div>
    </div>
    <script src="assets/js/jquery.min.js"></script>
    <script src="assets/bootstrap/js/bootstrap.min.js"></script>
    <script src="assets/js/bs-init.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/notyf@3/notyf.min.js"></script>
    <script src="assets/js/jquery.zoom.min.js"></script>
    <script src="assets/js/main.js"></script>
</body>

</html>
)=====";
