const char Index[] PROGMEM = R"=====(
<html>
<head>
    <title>Hack-en BadUSB</title>
    <meta charset="utf-8">
    <link rel="stylesheet" href="style.css">
    <script src="lib.js"></script>
</head>
<body>
<body>
<nav id='menu'>
                <input type='checkbox' id='responsive-menu' onclick='updatemenu()'><label></label>
                <ul>
                        <li><a href='/'>Home</a></li>
                        <li><a href='/livepayload'>Live Payload</a></li>
                        <li><a href='/uploadpayload'>Upload Payload</a></li>
                        <li><a href='/listpayloads'>List Payloads</a></li>
                </li>
                <div></div>
                </ul>
                </nav>
<br>
<hr>
<br>
<iframe style="visibility: hidden;" src="http://" )+local_IPstr+"/" name="iframe"></iframe>
</body>
</html>
)=====";
