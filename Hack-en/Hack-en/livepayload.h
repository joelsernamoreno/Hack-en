const char LivePayload[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
        <head>
                <title>Live Payload</title>
                <meta charset="utf-8">
                <link rel="stylesheet" href="style.css">
                <script src="lib.js"></script>
        </head>
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

                <FORM action="/runlivepayload" method="post" id="config" target="iframe">
                  <hr>
                  <p>Payload: </p><textarea class="css-input-text" form="config" rows="30" cols="50" name="livepayload"></textarea>
                  <hr>
                  <INPUT type="radio" name="configmodule" value="1" hidden="1" checked="checked">
                  <INPUT class="button-submit" type="submit" value="Run Payload">
                </form>
<br>
<hr>
<br>
<iframe style="visibility: hidden;" src="http://" )+local_IPstr+"/runlivepayload" name="iframe"></iframe>
</body>
</html>
)=====";
