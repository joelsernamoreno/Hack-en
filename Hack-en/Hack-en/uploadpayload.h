const char UploadPayload[] PROGMEM = R"=====(
<html>
  <head>
    <title>Upload Payload</title>
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
<hr>
<br>
<form method='POST' action='/upload' enctype='multipart/form-data'><input class="defBtn" type='file' name='upload'><br><br><input class="defBtn" type='submit' value='Upload'>
</form> 
</body>
)=====";
