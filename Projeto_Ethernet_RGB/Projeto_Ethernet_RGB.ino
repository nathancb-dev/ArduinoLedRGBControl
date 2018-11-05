#include "Modulo_Top.h"

#include "Modulo_Ethernet.h"
#include "Modulo_RGB.h"
#include "Modulo_LCD.h"
#include "Modulo_Botoes.h"

#include "Modulo_Temporario.h"

void setup() {
  initTop();

  initLCD();
  initRGB();
  initEthernet();
  initTemporario();
  initBotoes();
}

void loop() {
  MethodLCD();
  MethodRGB();
  MethodEthernet();
  MethodTemporario();
  MethodBotoes();
}
