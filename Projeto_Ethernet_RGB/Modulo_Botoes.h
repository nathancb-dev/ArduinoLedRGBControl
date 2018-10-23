// ================ Variaveis ================
bool pressedEnter;
// ============== End Variaveis ==============
// ================= Millis ==================
const int timeBtn = 250;
unsigned long tBtn;
unsigned long tPressedEnter;
// =============== End Millis ================

void initBotoes() {

}

void MethodBotoes() {
  if (tBtn <= millis()) {

    if (!digitalRead(BT1)) {

      if (innerTela == 0) {
        tela--;
        if (tela < 0) tela = 0;
      }

      if (tela == 2) {
        if (innerTela == 1) {
          r1--;
          if (r1 < 0) r1 = 0;
        } else if (tela == 3) {
          g1--;
          if (g1 < 0) g1 = 0;
        } else if (tela == 4) {
          b1--;
          if (b1 < 0) b1 = 0;
        }
      }

    } else if (!digitalRead(BT2)) {

      if (innerTela == 0) {
        tela++;
        if (tela > maxTela) tela = maxTela;
      }


      if (tela == 2) {
        r1++;
        if (r1 > 255) r1 = 255;
      } else if (tela == 3) {
        g1++;
        if (g1 > 255) g1 = 255;
      } else if (tela == 4) {
        b1++;
        if (b1 > 255) b1 = 255;
      }

    }

    showTela(tela);
    tBtn = millis() + timeBtn;
  }

  if (!digitalRead(BT3)) {

    if (millis() >= tPressedEnter + 1000) {
      innerTela -= 1;
      if (innerTela < 0) innerTela = 0;
      showTela(tela);
      pressedEnter = false;
    } else {
      pressedEnter = true;
    }

  } else {
    if (millis() >= tPressedEnter + 50 && pressedEnter) {
      innerTela += 1;
      if (innerTela > limitInnerTela) innerTela = limitInnerTela;
      showTela(tela);
    }
    pressedEnter = false;
    tPressedEnter = millis();
  }
}
