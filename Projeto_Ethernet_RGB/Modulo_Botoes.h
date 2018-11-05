// ================ Variaveis ================
bool pressedEnter;
bool controlPressedEnter;
// ============== End Variaveis ==============
// ================= Millis ==================
const int timeBtn = 300;
unsigned long tBtn;
unsigned long tPressedEnter;
// =============== End Millis ================

void initBotoes() {

}

void MethodBotoes() {
  if (tBtn <= millis()) {

    if (!digitalRead(BT1)) {

      if (!changingValue) {
        screenPath[screenDepth]--;
        if (screenPath[screenDepth] < 0 && screenLateralLimit > 0) screenPath[screenDepth] = screenLateralLimit - 1;

        showTela();
      } else {
        *vChangingValue--;
        if(*vChangingValue < 0) *vChangingValue = 0;
      }


      tBtn = millis() + timeBtn;
    } else if (!digitalRead(BT2)) {

      if (!changingValue) {
        screenPath[screenDepth]++;
        if (screenPath[screenDepth] >= screenLateralLimit && screenLateralLimit > 0) screenPath[screenDepth] = 0;

        showTela();
      } else {
        *vChangingValue++;
        if(*vChangingValue > 255) *vChangingValue = 255;
      }


      tBtn = millis() + timeBtn;
    }

  }

  if (!digitalRead(BT3)) {

    if (millis() >= tPressedEnter + 1000) { // pressed
      screenDepth -= 1;
      if (screenDepth < 0) screenDepth = 0;
      showTela();
      pressedEnter = false;
      controlPressedEnter = false;
      tPressedEnter = millis();
    } else {
      pressedEnter = true;
    }

  } else {
    if (millis() >= tPressedEnter + 50 && pressedEnter && controlPressedEnter) { // click
      screenDepth += 1;
      if (screenDepth > screenDepthLimit) screenDepth = screenDepthLimit;
      showTela();
    } else {
      controlPressedEnter = true;
    }
    pressedEnter = false;
    tPressedEnter = millis();
  }
}
