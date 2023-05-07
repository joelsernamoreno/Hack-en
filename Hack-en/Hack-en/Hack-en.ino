#include "hidkeyboard.h"
#include <WiFiClient.h> 
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFSEditor.h>
#include <EEPROM.h>
#include <FS.h>
#include <SPIFFS.h>
#include "SPI.h"
#include <WiFiAP.h>
#include "index.h"
#include "livepayload.h"
#include "uploadpayload.h"
#include "style.h"

#define FILESYSTEM SPIFFS
#define FORMAT_FILESYSTEM false

// Config default SSID, password and channel
const char* ssid = "Hacken";  // Enter your SSID here
const char* password = "123456789";  //Enter your Password here
const int wifi_channel = 1; //Enter your preferred Wi-Fi Channel

const bool formatOnFail = true;
String cmd;
char Command[255];
String tmp_key;
String tmp_mod;
uint8_t SomeKey;
uint8_t SomeMod;
String FileName;
String FileList;
int payload_state = 0;
String livepayload;

File fsUploadFile;

WebServer controlserver(80);
HIDkeyboard Keyboard;

void ProcessMod() {
  if (tmp_mod == "MOD_CTRL_LEFT") SomeMod = KEYBOARD_MODIFIER_LEFTCTRL;
  if (tmp_mod == "MOD_SHIFT_LEFT") SomeMod = KEYBOARD_MODIFIER_LEFTSHIFT;
  if (tmp_mod == "MOD_ALT_LEFT") SomeMod = KEYBOARD_MODIFIER_LEFTALT;
  if (tmp_mod == "MOD_GUI_LEFT") SomeMod = KEYBOARD_MODIFIER_LEFTGUI;
  if (tmp_mod == "MOD_CTRL_RIGHT") SomeMod = KEYBOARD_MODIFIER_RIGHTCTRL;
  if (tmp_mod == "MOD_SHIFT_RIGHT") SomeMod = KEYBOARD_MODIFIER_RIGHTSHIFT;
  if (tmp_mod == "MOD_ALT_RIGHT") SomeMod = KEYBOARD_MODIFIER_RIGHTALT;
  if (tmp_mod == "MOD_GUI_RIGHT") SomeMod = KEYBOARD_MODIFIER_RIGHTGUI;
}

void ProcessKey() {
  if (tmp_key == "KEY_ENTER") SomeKey = HID_KEY_ENTER;
  if (tmp_key == "KEY_CTRL_LEFT") SomeKey = HID_KEY_CONTROL_LEFT;
  if (tmp_key == "KEY_SHIFT_LEFT") SomeKey = HID_KEY_SHIFT_LEFT;
  if (tmp_key == "KEY_ALT_LEFT") SomeKey = HID_KEY_ALT_LEFT;
  if (tmp_key == "KEY_GUI_LEFT") SomeKey = HID_KEY_GUI_LEFT;
  if (tmp_key == "KEY_CTRL_RIGHT") SomeKey = HID_KEY_CONTROL_RIGHT;
  if (tmp_key == "KEY_SHIFT_RIGHT") SomeKey = HID_KEY_SHIFT_RIGHT;
  if (tmp_key == "KEY_ALT_RIGHT") SomeKey = HID_KEY_ALT_RIGHT;
  if (tmp_key == "KEY_GUI_RIGHT") SomeKey = HID_KEY_GUI_RIGHT;
  if (tmp_key == "KEY_ARROW_UP") SomeKey = HID_KEY_ARROW_UP;
  if (tmp_key == "KEY_ARROW_DOWN") SomeKey = HID_KEY_ARROW_DOWN;
  if (tmp_key == "KEY_ARROW_LEFT") SomeKey = HID_KEY_ARROW_LEFT;
  if (tmp_key == "KEY_ARROW_RIGHT") SomeKey = HID_KEY_ARROW_RIGHT;
  if (tmp_key == "KEY_BACKSPACE") SomeKey = HID_KEY_BACKSPACE;
  if (tmp_key == "KEY_TAB") SomeKey = HID_KEY_TAB;
  if (tmp_key == "KEY_PAUSE") SomeKey = HID_KEY_PAUSE;
  if (tmp_key == "KEY_INSERT") SomeKey = HID_KEY_INSERT;
  if (tmp_key == "KEY_DELETE") SomeKey = HID_KEY_DELETE;
  if (tmp_key == "KEY_PAGE_UP") SomeKey = HID_KEY_PAGE_UP;
  if (tmp_key == "KEY_PAGE_DOWN") SomeKey = HID_KEY_PAGE_DOWN;
  if (tmp_key == "KEY_ESCAPE") SomeKey = HID_KEY_ESCAPE;
  if (tmp_key == "KEY_SPACE") SomeKey = HID_KEY_SPACE;
  if (tmp_key == "KEY_MINUS") SomeKey = HID_KEY_MINUS;
  if (tmp_key == "KEY_BACKSLASH") SomeKey = HID_KEY_BACKSLASH;
  if (tmp_key == "KEY_HOME") SomeKey = HID_KEY_HOME;
  if (tmp_key == "KEY_END") SomeKey = HID_KEY_END;
  if (tmp_key == "KEY_CAPS_LOCK") SomeKey = HID_KEY_CAPS_LOCK;
  if (tmp_key == "KEY_PRINT_SCREEN") SomeKey = HID_KEY_PRINT_SCREEN;
  if (tmp_key == "KEY_SCROLL_LOCK") SomeKey = HID_KEY_SCROLL_LOCK;
  if (tmp_key == "KEY_NUM_LOCK") SomeKey = HID_KEY_NUM_LOCK;
  if (tmp_key == "KEY_F1") SomeKey = HID_KEY_F1;
  if (tmp_key == "KEY_F2") SomeKey = HID_KEY_F2;
  if (tmp_key == "KEY_F3") SomeKey = HID_KEY_F3;
  if (tmp_key == "KEY_F4") SomeKey = HID_KEY_F4;
  if (tmp_key == "KEY_F5") SomeKey = HID_KEY_F5;
  if (tmp_key == "KEY_F6") SomeKey = HID_KEY_F6;
  if (tmp_key == "KEY_F7") SomeKey = HID_KEY_F7;
  if (tmp_key == "KEY_F8") SomeKey = HID_KEY_F8;
  if (tmp_key == "KEY_F9") SomeKey = HID_KEY_F9;
  if (tmp_key == "KEY_F10") SomeKey = HID_KEY_F10;
  if (tmp_key == "KEY_F11") SomeKey = HID_KEY_F11;
  if (tmp_key == "KEY_F12") SomeKey = HID_KEY_F12;
  if (tmp_key == "KEY_A") SomeKey = HID_KEY_A;
  if (tmp_key == "KEY_B") SomeKey = HID_KEY_B;
  if (tmp_key == "KEY_C") SomeKey = HID_KEY_C;
  if (tmp_key == "KEY_D") SomeKey = HID_KEY_D;
  if (tmp_key == "KEY_E") SomeKey = HID_KEY_E;
  if (tmp_key == "KEY_F") SomeKey = HID_KEY_F;
  if (tmp_key == "KEY_G") SomeKey = HID_KEY_G;
  if (tmp_key == "KEY_H") SomeKey = HID_KEY_H;
  if (tmp_key == "KEY_I") SomeKey = HID_KEY_I;
  if (tmp_key == "KEY_J") SomeKey = HID_KEY_J;
  if (tmp_key == "KEY_K") SomeKey = HID_KEY_K;
  if (tmp_key == "KEY_L") SomeKey = HID_KEY_L;
  if (tmp_key == "KEY_M") SomeKey = HID_KEY_M;
  if (tmp_key == "KEY_N") SomeKey = HID_KEY_N;
  if (tmp_key == "KEY_O") SomeKey = HID_KEY_O;
  if (tmp_key == "KEY_P") SomeKey = HID_KEY_P;
  if (tmp_key == "KEY_Q") SomeKey = HID_KEY_Q;
  if (tmp_key == "KEY_R") SomeKey = HID_KEY_R;
  if (tmp_key == "KEY_S") SomeKey = HID_KEY_S;
  if (tmp_key == "KEY_T") SomeKey = HID_KEY_T;
  if (tmp_key == "KEY_U") SomeKey = HID_KEY_U;
  if (tmp_key == "KEY_V") SomeKey = HID_KEY_V;
  if (tmp_key == "KEY_W") SomeKey = HID_KEY_W;
  if (tmp_key == "KEY_X") SomeKey = HID_KEY_X;
  if (tmp_key == "KEY_Y") SomeKey = HID_KEY_Y;
  if (tmp_key == "KEY_Z") SomeKey = HID_KEY_Z;
  if (tmp_key == "KEY_1") SomeKey = HID_KEY_1;
  if (tmp_key == "KEY_2") SomeKey = HID_KEY_2;
  if (tmp_key == "KEY_3") SomeKey = HID_KEY_3;
  if (tmp_key == "KEY_4") SomeKey = HID_KEY_4;
  if (tmp_key == "KEY_5") SomeKey = HID_KEY_5;
  if (tmp_key == "KEY_6") SomeKey = HID_KEY_6;
  if (tmp_key == "KEY_7") SomeKey = HID_KEY_7;
  if (tmp_key == "KEY_8") SomeKey = HID_KEY_8;
  if (tmp_key == "KEY_9") SomeKey = HID_KEY_9;
  if (tmp_key == "KEY_0") SomeKey = HID_KEY_0;
}

/*void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
  String logmessage = "Client:" + request->client()->remoteIP().toString() + " " + request->url();

  if (!index) {
    logmessage = "Upload Start: " + String(filename);
    request->_tempFile = SPIFFS.open("/payloads/" + filename, "w");
  }

  if (len) {
    request->_tempFile.write(data, len);
    logmessage = "Writing file: " + String(filename) + " index=" + String(index) + " len=" + String(len);
  }

  if (final) {
    logmessage = "Upload Complete: " + String(filename) + ",size: " + String(index + len);
    request->_tempFile.close();
    request->redirect("/");
  }
}*/

void deleteFile(fs::FS &fs, String path){
  if(fs.remove(path)){
  }
}

void readFile(fs::FS &fs, String path){
  FileList = "<!DOCTYPE HTML><html><head><title>Show Payload</title><meta charset=\"utf-8\"><link rel=\"stylesheet\" href=\"style.css\"><script src=\"lib.js\"></script></head><body><nav id='menu'><input type='checkbox' id='responsive-menu' onclick='updatemenu()'><label></label><ul><li><a href='/'>Home</a></li><li><a href='/livepayload'>Live Payload</a></li><li><a href='/uploadpayload'>Upload Payload</a></li><li><a href='/listpayloads'>List Payloads</a></li></ul></li></li><div></div></ul></nav><br><hr><p>Payload: </p></h>";    
  cmd = "";
  File file = fs.open(path);
  
  if(!file || file.isDirectory()){
    return;
  }

  while(file.available()){
    cmd = file.readString();
    FileList += " ";
    FileList += "<h2><pre>"+FileName+"\n-----\n"+cmd+"</pre></h2>";
  }
  file.close();
  livepayload = cmd;
  FileList += "<FORM action=\"/dopayload\" method=\"post\" id=\"config\" target=\"iframe\"><hr><INPUT type=\"radio\" name=\"configmodule\" value=\"1\" hidden=\"1\" checked=\"checked\"><INPUT class=\"defBtn\" type=\"submit\" value=\"Run Payload\"></form><br><FORM action=\"/deletepayload\" method=\"post\" id=\"config\" target=\"iframe\"><hr><INPUT type=\"radio\" name=\"configmodule\" value=\"1\" hidden=\"1\" checked=\"checked\"><INPUT class=\"defBtn\" type=\"submit\" value=\"Delete Payload\"></form><iframe style=\"visibility: hidden;\" src=\"http://\" )+local_IPstr+\"/dopayload\" name=\"iframe\"></iframe></body></html>";
} 

void handleFileUpload() {
  HTTPUpload& upload = controlserver.upload();
  
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    
    if (!filename.startsWith("/")) {
      filename = "/payloads/" + filename;
    }
    
    fsUploadFile = FILESYSTEM.open(filename, "w");
    delay(500);
    filename = String();
    
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (fsUploadFile) {
      delay(500);
      fsUploadFile.write(upload.buf, upload.currentSize);
      delay(1000);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      delay(1000);
      fsUploadFile.close();
    }
  }
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  FileList = "<!DOCTYPE HTML><html><head><title>Choose Payload</title><meta charset=\"utf-8\"><link rel=\"stylesheet\" href=\"style.css\"><script src=\"lib.js\"></script></head><body><nav id='menu'><input type='checkbox' id='responsive-menu' onclick='updatemenu()'><label></label><ul><li><a href='/'>Home</a></li></li><li><a href='/livepayload'>Live Payload</a></li><li><a href='/uploadpayload'>Upload Payload</a></li><li><a href='/listpayloads'>List Payloads</a></li></ul></li></li><div></div></ul></nav><br><hr><p>Choose Payload: </p></h><br>";
  File root = fs.open(dirname);
  
  if(!root){
    return;
  }
  if(!root.isDirectory()){
    return;
  }

  if (root.isDirectory()) {
    File file = root.openNextFile();
    while (file) {
      FileName = "/payloads/";
      FileName += file.name();
      FileList += " ";
      FileList += "<a class=\"myButton\" href=\"/showpayload?payload="+FileName+"\">"+FileName+"</a>"+"<br><br>";

      file = root.openNextFile();
    }
  }
  FileList += "</body></html>";
}

void payloadExec(){
  
  if(cmd.startsWith("RunMac ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    Keyboard.sendPress(HID_KEY_SPACE, KEYBOARD_MODIFIER_LEFTGUI);
    delay(100);
    Keyboard.sendRelease();
    delay(2000);
    Keyboard.sendString(Command + 7);
    delay(100);
    Keyboard.sendString("\n");
  }

  else if(cmd.startsWith("RunUnix ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    Keyboard.sendPress(HID_KEY_F2, KEYBOARD_MODIFIER_LEFTALT);
    delay(100);
    Keyboard.sendRelease();
    delay(2000);
    Keyboard.sendString(Command + 8);
    delay(100);
    Keyboard.sendString("\n");
  }

  else if(cmd.startsWith("RunWin ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    Keyboard.sendPress(HID_KEY_R, KEYBOARD_MODIFIER_LEFTGUI);
    delay(100);
    Keyboard.sendRelease();
    delay(2000);
    Keyboard.sendString(Command + 7);
    delay(100);
    Keyboard.sendString("\n");
  }

  else if(cmd == "AltF2"){
    Keyboard.sendPress(HID_KEY_F2, KEYBOARD_MODIFIER_LEFTALT);
    delay(100);
    Keyboard.sendRelease();
  }

  else if(cmd == "GuiR"){
    Keyboard.sendPress(HID_KEY_R, KEYBOARD_MODIFIER_LEFTGUI);
    delay(100);
    Keyboard.sendRelease();
  }

  else if(cmd == "GuiSpace"){
    Keyboard.sendPress(HID_KEY_SPACE, KEYBOARD_MODIFIER_LEFTGUI);
    delay(100);
    Keyboard.sendRelease();
  }

  else if(cmd.startsWith("PrintLine ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    Keyboard.sendString(Command + 10);
    delay(100);
    Keyboard.sendString("\n");
  }

  else if(cmd.startsWith("Print ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    Keyboard.sendString(Command + 6);
  }

  else if(cmd.startsWith("PressModKey ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    String tmp_cmd = Command + 12;
    int str_len = tmp_cmd.length()+1;
    int index = tmp_cmd.indexOf(' ');
    tmp_mod = tmp_cmd.substring(0, index);
    ProcessMod();
    tmp_key = tmp_cmd.substring(index+1, str_len);
    ProcessKey();
    delay(100);
    Keyboard.sendPress(SomeKey, SomeMod);
    delay(100);
    Keyboard.sendRelease();
  }

  else if(cmd.startsWith("PressKey ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    tmp_key = Command + 9;
    ProcessKey();
    Keyboard.sendPress(SomeKey, 0);
    delay(100);
    Keyboard.sendRelease();
  }

  else if(cmd.startsWith("Release")) {
    Keyboard.sendRelease();
  }

  else if(cmd.startsWith("Delay ")){
    cmd.toCharArray(Command, cmd.length() + 1);
    delay(atoi(Command + 6));
  }
}

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password,wifi_channel,8);
  
  Keyboard.begin();
  
  if (FORMAT_FILESYSTEM) FILESYSTEM.format();
  FILESYSTEM.begin();
  {
      File root = FILESYSTEM.open("/payloads/");
      File file = root.openNextFile();
      while(file){
          String fileName = file.name();
          size_t fileSize = file.size();
          file = root.openNextFile();
      }
  }

  controlserver.on("/", []() {
    controlserver.send_P(200, "text/html", Index);
  });

  controlserver.on("/livepayload", []() {
    controlserver.send_P(200, "text/html", LivePayload);
  });

  controlserver.on("/style.css", []() {
    controlserver.send_P(200, "text/css", Style);
  });

  controlserver.on("/uploadpayload", []() {
    controlserver.send_P(200, "text/html", UploadPayload);
  });

  controlserver.on("/upload", HTTP_POST, []() {
    controlserver.send(200, "text/plain", "");
  }, handleFileUpload);

  controlserver.on("/listpayloads", []() {
    listDir(SPIFFS, "/payloads", 0);
    controlserver.send(200, "text/html", FileList);
  });

  controlserver.on("/showpayload", []() {
    FileName = controlserver.arg(String("payload"));
    readFile(SPIFFS, FileName);
    controlserver.send(200, "text/html", FileList);
  });

  controlserver.on("/dopayload", [](){     
    if (livepayload != "") {
      payload_state = 1;
    }
  });

  controlserver.on("/runlivepayload", [](){
    livepayload = controlserver.arg("livepayload");
    if (controlserver.arg("configmodule")) {
      payload_state = 1;
    }
  });

  controlserver.on("/deletepayload", [](){
    if (controlserver.arg("configmodule")) {
      deleteFile(SPIFFS, FileName);
    }
  });
  
  controlserver.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  controlserver.handleClient();
  vTaskDelay(1);
  
  if(payload_state == 1) {
    char* splitlines;
    int payloadlen = livepayload.length()+1;
    char request[payloadlen];
    livepayload.toCharArray(request,payloadlen);
    splitlines = strtok(request,"\r\n");

    while(splitlines != NULL) {
      cmd = splitlines;       
      payloadExec();
      splitlines = strtok(NULL,"\r\n");
      vTaskDelay(1);
    }
      payload_state = 0;
      cmd = "";
      return;
      livepayload = "";
  }
}
