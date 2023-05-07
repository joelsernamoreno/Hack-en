#include "hidkeyboard.h"
HIDkeyboard Keyboard;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  Keyboard.begin();

  Keyboard.sendKey(HID_KEY_A);
  delay(1000);
  Keyboard.sendString("123456789\n");
  delay(1000);
  Keyboard.sendString("abcdefghijklmnopqrstUvwxYz\n");
  delay(1000);
  Keyboard.sendPress(HID_KEY_F2, KEYBOARD_MODIFIER_LEFTALT);
  delay(100);
  Keyboard.sendRelease();
  delay(1000);
  Keyboard.sendString("Hello World");
}

void loop() {
  // put your main code here, to run repeatedly:

}
