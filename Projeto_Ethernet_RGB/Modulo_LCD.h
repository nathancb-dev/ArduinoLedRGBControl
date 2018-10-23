// ================ Variaveis ================
int contrasteLCD = 110; // valor mais adequado
int tela = 2;
int maxTela = 4;
bool show = true;

bool subTelaOF;

int innerTela;
int limitInnerTela;

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

void MethodLCD() {
  if (show) {

    lcd.clear();
    lcd.write(B00111100); // <
    lcd.setCursor(15, 0);
    lcd.write(B00111110); // >

    if (tela == 0) {
      lcd.setCursor(3, 0);
      lcd.print("Server IP:");
      lcd.setCursor(0, 1);
      lcd.print("192.168.0.150");
    } else if (tela == 1) {
      lcd.setCursor(1, 0);
      lcd.print("Funciona Karai");
      lcd.setCursor(7, 1);
      lcd.write(byte(1));
    } else if (tela == 2) {
      lcd.setCursor(1, 0);
      lcd.print("Config RGB (1)");

      lcd.setCursor(1, 1);
      lcd.print("R");
      lcd.print(r1);

      lcd.setCursor(6, 1);
      lcd.print("G");
      lcd.print(g1);

      lcd.setCursor(11, 1);
      lcd.print("B");
      lcd.print(b1);
    }

    show = false;
  }

  if (tela == 2) {
    if (tela == 2) {
      lcd.setCursor(2, 1);
      SetRGBPisca(r1);
    } else if (tela == 3) {
      lcd.setCursor(7, 1);
      SetRGBPisca(g1);
    } else if (tela == 4) {
      lcd.setCursor(12, 1);
      SetRGBPisca(b1);
    }
  }
}

void showTela(int n) {
  tela = n;
  show = true;
}
