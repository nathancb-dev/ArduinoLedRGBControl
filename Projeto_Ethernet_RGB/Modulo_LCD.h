// ================ Variaveis ================
int contrasteLCD = 110; // valor mais adequado
int tela = 2;
int maxTela = 4;
bool show = true;

bool subTelaOF;

int innerTela;
int limitInnerTela;

int screenDepth;
int screenDepthLimit; // limite de profundidade
int screenPath[6]; // caminhos por onde as screen são buscadas
int screenLateralLimit;

// ============== End Variaveis ==============
// ================= Millis ==================
const int timePisca = 500;
unsigned long tPiscaSet;
// =============== End Millis ================

void initLCD() {
  analogWrite(PContrasteLCD, contrasteLCD);

  lcd.begin(16, 2);
  lcd.print("Inicializando...");
}

void SetRGBPisca(int value) {
  if (subTelaOF || !digitalRead(BT2) || !digitalRead(BT1)) {
    lcd.print(value);
  } else {
    lcd.print("   ");
  }

  if (tPiscaSet <= millis()) {
    subTelaOF = !subTelaOF;
    tPiscaSet = millis() + timePisca;
  }
}

void showArrow(int line, int start, int end) {
  lcd.setCursor(start, line);
  lcd.write(B00111100); // <
  lcd.setCursor(end, line);
  lcd.write(B00111110); // >
}

void MethodLCD() {
  if (show) {

    lcd.clear();
    switch (screenPath[0]) {
      case 0:
        lcd.setCursor(4, 0);
        lcd.print("Stand-By");
        if (screenDepth >= 1) {
          lcd.setCursor(1, 1);
          switch (screenPath[1]) {
            case 0:
              lcd.print("Spectrum Ana..");
              screenLateralLimit = 2;
              screenDepthLimit = 1;
              break;
            case 1:
              lcd.print("Float.. Circle");
              screenLateralLimit = 2;
              screenDepthLimit = 1;
              break;
          }
          showArrow(1, 0, 15);
        } else {
          showArrow(0, 0, 15);
          screenLateralLimit = 4;
          screenDepthLimit = 1;
        }
        break;
      case 1:
        lcd.setCursor(3, 0);
        lcd.print("Server IP:");
        lcd.setCursor(0, 1);
        lcd.print("192.168.0.150");
        showArrow(0, 0, 15);
        screenLateralLimit = 4;
        screenDepthLimit = 0;
        break;
      case 2:


        //==========================================
        lcd.setCursor(2, 0);
        lcd.print("RGB  Effects");
        showArrow(0, 0, 15);
        screenLateralLimit = 4;
        screenDepthLimit = 0;
        //==========================================


        break;
      case 3:
        if (screenDepth >= 1) {
          switch (screenPath[1]) {
            case 0:
              if (screenDepth >= 2) {
                switch (screenPath[2]) {
                  case 0:
                    lcd.setCursor(4, 0);
                    lcd.print("Contrast");
                    lcd.setCursor(6, 1);
                    lcd.print("Cxxx");
                    showArrow(0, 0, 15);
                    screenLateralLimit = 2;
                    screenDepthLimit = 2;
                    break;
                  case 1:
                    lcd.setCursor(3, 0);
                    lcd.print("Brightness");
                    lcd.setCursor(6, 1);
                    lcd.print("Bxxx");
                    showArrow(0, 0, 15);
                    screenLateralLimit = 2;
                    screenDepthLimit = 2;
                    break;
                }
              } else {
                lcd.setCursor(4, 0);
                lcd.print("Settings");
                lcd.setCursor(2, 1);
                lcd.print("LCD  Display");
                showArrow(1, 0, 15);
                screenLateralLimit = 2;
                screenDepthLimit = 2;
              }
              break;
            case 1:
              if (screenDepth >= 2) {
                switch (screenPath[2]) {
                  case 0:
                    lcd.setCursor(2, 0);
                    lcd.print("Code Version");
                    lcd.setCursor(6, 1);
                    lcd.print("V0.x");
                    showArrow(0, 0, 15);
                    screenLateralLimit = 2;
                    screenDepthLimit = 2;
                    break;
                  case 1:
                    lcd.setCursor(1, 0);
                    lcd.print("Developer Name");
                    lcd.setCursor(2, 1);
                    lcd.print("Nathan C. B.");
                    showArrow(0, 0, 15);
                    screenLateralLimit = 2;
                    screenDepthLimit = 2;
                    break;
                }
              } else {
                lcd.setCursor(4, 0);
                lcd.print("Settings");
                lcd.setCursor(4, 1);
                lcd.print("About to");
                showArrow(1, 0, 15);
                screenLateralLimit = 2;
                screenDepthLimit = 2;
              }
              break;
          }
        } else {
          lcd.setCursor(4, 0);
          lcd.print("Settings");
          showArrow(0, 0, 15);
          screenLateralLimit = 4;
          screenDepthLimit = 1;
        }
        break;
    }

    show = false;
  }

  //  if (tela == 2) {
  //   if (tela == 2) {
  //      lcd.setCursor(2, 1);
  //      SetRGBPisca(r1);
  //    } else if (tela == 3) {
  //      lcd.setCursor(7, 1);
  //      SetRGBPisca(g1);
  //    } else if (tela == 4) {
  //      lcd.setCursor(12, 1);
  //      SetRGBPisca(b1);
  //    }
  //  }
}

void showTela() {
  show = true;
}
