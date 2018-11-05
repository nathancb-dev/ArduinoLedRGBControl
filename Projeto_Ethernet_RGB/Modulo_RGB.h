// ================ Variaveis ================
int efeito;
int r1 = 255;
int g1 = 255;
int b1 = 255;

// fade
int corfadeatual = 0;
int fade_break = 50; // tempo do fade
int rgbColour[3] = {255, 0, 0};

// ============== End Variaveis ==============
// ================= Millis ==================
unsigned long fade_goTime;
// =============== End Millis ================

void initRGB(){
  // testing RGB color
  analogWrite(RED1,255);
  analogWrite(RED2,255);
  delay(1000);
  analogWrite(RED1,0);
  analogWrite(RED2,0);
  
  analogWrite(GREEN1,255);
  analogWrite(GREEN2,255);
  delay(1000);
  analogWrite(GREEN1,0);
  analogWrite(GREEN2,0);
  
  analogWrite(BLUE1,255);
  analogWrite(BLUE2,255);
  delay(1000);
  analogWrite(BLUE1,0);
  analogWrite(BLUE2,0);
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(RED1, red);
  analogWrite(GREEN1, green);
  analogWrite(BLUE1, blue);
  
  analogWrite(RED2, red);
  analogWrite(GREEN2, green);
  analogWrite(BLUE2, blue);
}

void Fade() {
  if (millis() >= fade_goTime) {
    if (corfadeatual == 0) {
      rgbColour[1]++;
      if (rgbColour[1] >= 255) corfadeatual++;
    } else if (corfadeatual == 1) {
      rgbColour[0]--;
      if (rgbColour[0] <= 0) corfadeatual++;
    } else if (corfadeatual == 2) {
      rgbColour[2]++;
      if (rgbColour[2] >= 255) corfadeatual++;
    } else if (corfadeatual == 3) {
      rgbColour[1]--;
      if (rgbColour[1] <= 0) corfadeatual++;
    } else if (corfadeatual == 4) {
      rgbColour[0]++;
      if (rgbColour[0] >= 255) corfadeatual++;
    } else if (corfadeatual == 5) {
      rgbColour[2]--;
      if (rgbColour[2] <= 0) corfadeatual = 0;
    }
    setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
    fade_goTime = millis() + fade_break;
  }
}

void MethodRGB(){
  Fade();
}
