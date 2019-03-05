#include <JC_Button.h>
#include "module_buttons.h"

char c;
String str;
bool strInSerial;

void setup() {
  Serial.begin(9600);

  init_buttons();

  Serial.println("Started!");
}

void loop() {
  verifyButtons();
  if (Serial.available()) {
    c = Serial.read();
    str += c;
    strInSerial = true;
  } else {
    int s = str.indexOf("/strEnd");
    if (s > 0) {
      str = str.substring(0, s);
      invertPort(8); // teste
      Serial.print(str);
      str = "";
    }
  }
}
