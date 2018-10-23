//======PORTAS ARDUINO=======
// Porta do arduino Analog in: Entrada do Som
#define SOUND 0

// Porta do arduino Analog in: Entrada do LDR
#define LDR 1

// Porta do arduino Analog in: Entrada de leitura de Botao
#define BOTAO 5

// Porta da 1º fita de led (R, G, B), em sequencia
#define RED1 6
#define BLUE1 5
#define GREEN1 3

// Porta da 2º fita de led (R, G, B), em sequencia
#define RED2 9
#define BLUE2 10
#define GREEN2 11

//=======VARIAVEIS==========
// total de efeitos no programa
int totalefeitos = 6;

// Variaveis para rodar o Programa (Não alterar)
int sensibilidade = 520;
int corfadeatual;
int led;
int red1;
int red2;
int blue1;
int blue2;
int green1;
int green2;
int ldr;
int sound;
int botao;
int i = -1;
int efeito = 0;
bool luzligado;
int maior = sensibilidade;
int brilhomax = 255;
int incColour = 1;
int decColour = 0;
bool ligado = true;
bool luzterminada;
bool botao1ativado;
bool controlebotao1;
unsigned long delayflash;
unsigned long tempomillis;
unsigned long fade_goTime;
unsigned long delayluz;
unsigned long delaybotao;
unsigned long delaystrobo;
unsigned long tempocontador;
int rgbColour[3] = {brilhomax, 0, 0};
int tempostrobo = 50;
int contadorbotao1;
int efeitoritmico0;
int corstrobo;
int brilhoestavel;
int matbrilhosom ;
float multiplicadorbrilho = 1.0;
int attleds = 50;
byte efeitoritmico = 0;
int nivelefeito2 = 120;
int activationLDR = 850;
int luzstandby = 15;
int fade_break = 10;
int nconfig;
int configritmico;
int totalnconfig = 1;
bool configuracao = false;
int corstatica;
unsigned long fadecorunica;
int tempofadecorunica = 11000;
int auxtempofadecorunica;
unsigned long lasttimefadecorunica;
int brifadeuncio;
bool brifadeunciobool;
int luzmaxfadecorunica = 50;
int corred = 0;
int corgreen = 0;
int corblue = 0;
byte lastcorrgb;
int brilhocorstatica = 255;


void setup() {
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(BLUE1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  matbrilhosom = brilhoestavel + matbrilhosom;
  luzstandby = 255 / luzstandby;
  totalnconfig += 1;
}

void ResetEfeito() {
  for (int h = 0; h < 3; h++) {
    analogWrite(GREEN1, 0);
    analogWrite(GREEN2, 0);
    analogWrite(BLUE1, 0);
    analogWrite(BLUE2, 0);
    analogWrite(RED1, 0);
    analogWrite(RED2, 0);

    delay(150);

    analogWrite(GREEN1, 255);
    analogWrite(GREEN2, 255);
    analogWrite(BLUE1, 255);
    analogWrite(BLUE2, 255);
    analogWrite(RED1, 255);
    analogWrite(RED2, 255);

    delay(150);
  }
  if (efeito = -1) {
    efeito = 0;
  } else if (efeito == 0) {
    rgbColour[0] = brilhomax;
    rgbColour[1] = 0;
    rgbColour[2] = 0;
    i = -1;
    incColour = 1;
    decColour = 0;
    fade_break = 25;
  } else if (efeito == 1) {
    sensibilidade = 520;
    multiplicadorbrilho = 1.0;
    matbrilhosom = 0;
    nivelefeito2 = 120;
    efeitoritmico0 = 0;
    efeitoritmico = 0;
  } else if (efeito == 2) {
    corstrobo = 0;
    tempostrobo = 50;
  }
}

void Configuracao() {
  if (nconfig = 0) {
    analogWrite(GREEN1, 0);
    analogWrite(GREEN2, 0);
    analogWrite(BLUE1, 0);
    analogWrite(BLUE2, 0);
    analogWrite(RED1, 0);
    analogWrite(RED2, 0);

    delay(150);

    analogWrite(GREEN1, 255);
    analogWrite(GREEN2, 255);
    analogWrite(BLUE1, 255);
    analogWrite(BLUE2, 255);
    analogWrite(RED1, 255);
    analogWrite(RED2, 255);

    delay(150);

    red1 = 0;
    red2 = 0;
    green1 = 0;
    green2 = 0;
    blue1 = 0;
    blue2 = 0;

    nconfig = 1;
  } else {
    if (nconfig == 1) {
      red1 = brilhomax;
      red2 = brilhomax;
      green1 = brilhomax;
      green2 = brilhomax;
      blue1 = brilhomax;
      blue2 = brilhomax;
    }
  }
}

void Botao1() {
  if (botao1ativado) {
    if ((millis() - tempocontador) < 1500) {
      contadorbotao1 = 1;
      controlebotao1 = true;
    } else if ((millis() - tempocontador) < 5000) {
      if (efeito == 4) {
        configuracao = !configuracao;
      } else {
        contadorbotao1 = 2;
        controlebotao1 = true;
      }
    } else {
      contadorbotao1 = 0;
      analogWrite(GREEN1, 255);
      analogWrite(GREEN2, 255);
      analogWrite(BLUE1, 255);
      analogWrite(BLUE2, 255);
      analogWrite(RED1, 255);
      analogWrite(RED2, 255);
      delay(1000);
      ligado = false;
    }
  }
}

void Botao2() {
  if (efeito == 0) {
    fade_break -= 1;
    if (fade_break < 0) {
      fade_break = 0;
    }
    delaybotao = millis() + 250;
  } else if (efeito == 1) {
    if (efeitoritmico == 1 || efeitoritmico == 2) {
      if (configritmico == 0) {
        nivelefeito2 -= 5;
      } else if (configritmico == 1) {
        brilhoestavel -= 10;
        if (brilhoestavel < 0) {
          brilhoestavel = 0;
        } else {
          matbrilhosom -= 10;
        }
      } else if (configritmico == 2) {
        multiplicadorbrilho -= 0.05;
        if (multiplicadorbrilho < 0.3) {
          multiplicadorbrilho = 0.3;
        }
      }
    }
    delaybotao = millis() + 250;
  } else if (efeito == 2) {
    tempostrobo -= 10;
    if (tempostrobo < 20) {
      tempostrobo = 20;
    }
    delaybotao = millis() + 250;
  } else if (efeito == 3) {
    brilhocorstatica -= 10;
    if (brilhocorstatica < 20) {
      brilhocorstatica = 20;
    }
    rgbColour[0] = brilhomax;
    rgbColour[1] = 0;
    rgbColour[2] = 0;
    i = -1;
    incColour = 1;
    decColour = 0;
    delaybotao = millis() + 250;
  } else if (efeito == 4) {
    tempofadecorunica -= 100;
    if (tempofadecorunica < 500) {
      tempofadecorunica = 500;
    }
    delaybotao = millis() + 250;
  } else if (efeito == 5) {
    lastcorrgb = 1;
    corred += 5;
    if (corred > 255) {
      corred = 255;
    }
    delaybotao = millis() + 100;
  }
}

void Botao3() {
  if (efeito == 0) {
    fade_break += 1;
    delaybotao = millis() + 250;
  } else if (efeito == 1) {
    if (efeitoritmico == 1 || efeitoritmico == 2) {
      if (configritmico == 0) {
        nivelefeito2 += 5;
      } else if (configritmico == 1) {
        brilhoestavel += 10;
        matbrilhosom += 10;
      } else if (configritmico == 2) {
        multiplicadorbrilho += 0.05;
      }
    }
    delaybotao = millis() + 250;
  } else if (efeito == 2) {
    tempostrobo += 10;
    delaybotao = millis() + 250;
  } else if (efeito == 3) {
    brilhocorstatica += 10;
    if (brilhocorstatica > 255) {
      brilhocorstatica = 255;
    }
    rgbColour[0] = brilhomax;
    rgbColour[1] = 0;
    rgbColour[2] = 0;
    i = -1;
    incColour = 1;
    decColour = 0;
    delaybotao = millis() + 250;
  } else if (efeito == 4) {
    tempofadecorunica += 100;
    delaybotao = millis() + 250;
  } else if (efeito == 5) {
    lastcorrgb = 2;
    corgreen += 5;
    if (corgreen >= 255) {
      corgreen = 255;
    }
    delaybotao = millis() + 100;
  }
}

void Botao4() {
  if (efeito == 1) {
    if (efeitoritmico == 0) {
      efeitoritmico0++;
      if (efeitoritmico0 > 6) {
        efeitoritmico0 = 0;
      }
    } else {
      configritmico++;
      if (configritmico >= 3) {
        configritmico = 0;
      }
    }
    delaybotao = millis() + 300;
  } else if (efeito == 5) {
    lastcorrgb = 3;
    corblue += 5;
    if (corblue >= 255) {
      corblue = 255;
    }
    delaybotao = millis() + 100;
  }
}

void Botao5() {
  if (efeito == 1) {
    efeitoritmico++;
    if (efeitoritmico > 2) {
      efeitoritmico = 0;
    }
    delaybotao = millis() + 500;
  } else if (efeito == 2) {
    corstrobo++;
    if (corstrobo > 6) {
      corstrobo = 0;
    }
    delaybotao = millis() + 500;
  } else if (efeito == 3) {
    corstatica++;
    if (corstatica > 6) {
      corstatica = 0;
    }
    delaybotao = millis() + 500;
  } else if (efeito == 5) {
    if (lastcorrgb == 1) {
      corred -= 5;
      if (corred <= 0) {
        corred = 0;
      }
    } else if (lastcorrgb == 2) {
      corgreen -= 5;
      if (corgreen <= 0) {
        corgreen = 0;
      }
    } else if (lastcorrgb == 3) {
      corblue -= 5;
      if (corblue <= 0) {
        corblue = 0;
      }
    }
    delaybotao = millis() + 100;
  }
}

void Botoes() {
  if (millis() > delaybotao) {
    if (botao >= 1015 && botao <= 1023) {
      Botao1();
    } else if (botao >= 500 && botao <= 520) {
      Botao2();
    } else if (botao >= 330 && botao <= 350) {
      Botao3();
    } else if (botao >= 245 && botao <= 265) {
      Botao4();
    } else if (botao >= 180 && botao <= 220) {
      Botao5();
    } else {
      if (controlebotao1) {
        if (contadorbotao1 == 1) {
          if (configuracao) {
            nconfig++;
            if (nconfig >= totalnconfig) {
              nconfig = 1;
            }
          } else {
            efeito++;
            if (efeito >= totalefeitos) {
              efeito = 0;
            }
          }
          delaybotao = millis() + 500;
        } else if (contadorbotao1 == 2) {
          if (configuracao) {
            nconfig = 0;
            Configuracao();
          } else {
            ResetEfeito();
          }
        }
        controlebotao1 = false;
      }
      tempocontador = millis();
      botao1ativado = true;
    }
  }
}

void LuzNoturna() {
  if (millis() > delayluz && luzligado == false && luzterminada == false) {
    green1 -= luzstandby;
    green2 -= luzstandby;
    if (green1 <= 0) {
      red1 = 0;
      red2 = 0;
      green1 = 0;
      green2 = 0;
      blue1 = 0;
      blue2 = 0;
      luzterminada = true;
    }
    delayluz = millis() + 1000;
  }
}

void Desligado() {
  if (ldr > activationLDR) {
    if (millis() > delayflash) {
      if (luzligado) {
        green1 = brilhomax;
        green2 = brilhomax;
        red1 = 0;
        red2 = 0;
        blue1 = 0;
        blue2 = 0;
        luzligado = false;
        luzterminada = false;
      }
      LuzNoturna();
    }
  } else {
    luzligado = true;
    green1 = 0;
    green2 = 0;
    red1 = 0;
    red2 = 0;
    blue1 = 0;
    blue2 = 0;
    delayflash = millis() + 250;
  }

  if (botao >= 180 && botao <= 220) {
    if ((millis() - tempocontador) > 1000) {
      efeito = -1;
      ResetEfeito();
      ligado = true;
    }
  } else {
    tempocontador = millis();
  }
}

void Ritmico() {
  if (millis() < tempomillis) {
    if (sound > maior) {
      maior = sound;
    }
  } else {
    if (maior > sensibilidade) {
      led = ((maior - sensibilidade) * multiplicadorbrilho) + matbrilhosom;
      if (led >= brilhomax) {
        led = brilhomax;
      }
    } else {
      led = brilhoestavel;
    }

    if (efeitoritmico == 0) {
      if (efeitoritmico0 == 0) {
        red1 = led;
        red2 = led;
        green1 = led;
        green2 = led;
        blue1 = led;
        blue2 = led;
      } else if (efeitoritmico0 == 1) {
        red1 = led;
        red2 = led;
        green1 = 0;
        green2 = 0;
        blue1 = 0;
        blue2 = 0;
      } else if (efeitoritmico0 == 2) {
        red1 = led;
        red2 = led;
        green1 = led;
        green2 = led;
        blue1 = 0;
        blue2 = 0;
      } else if (efeitoritmico0 == 3) {
        red1 = 0;
        red2 = 0;
        green1 = led;
        green2 = led;
        blue1 = 0;
        blue2 = 0;
      } else if (efeitoritmico0 == 4) {
        red1 = 0;
        red2 = 0;
        green1 = led;
        green2 = led;
        blue1 = led;
        blue2 = led;
      } else if (efeitoritmico0 == 5) {
        red1 = 0;
        red2 = 0;
        green1 = 0;
        green2 = 0;
        blue1 = led;
        blue2 = led;
      } else if (efeitoritmico0 == 6) {
        red1 = led;
        red2 = led;
        green1 = 0;
        green2 = 0;
        blue1 = led;
        blue2 = led;
      }
    } else if (efeitoritmico == 1) {
      if (led == 0) {
        led = brilhoestavel;
        red1 = led;
        red2 = led;
        green1 = led;
        green2 = led;
        blue1 = led;
        blue2 = led;
      } else if (led < nivelefeito2) {
        led = map(led, 0, nivelefeito2 - 1, 0, brilhomax);
        red1 = 0;
        red2 = 0;
        green1 = led;
        green2 = led;
        blue1 = 0;
        blue2 = 0;
      } else {
        led = map(led, nivelefeito2, brilhomax, 0, brilhomax);
        red1 = led;
        red2 = led;
        green1 = 0;
        green2 = 0;
        blue1 = 0;
        blue2 = 0;
      }
    } else if (efeitoritmico == 2) {
      if (led == 0) {
        led = brilhoestavel;
        red1 = led;
        red2 = led;
        green1 = led;
        green2 = led;
        blue1 = led;
        blue2 = led;
      } else if (led < nivelefeito2) {
        red1 = 0;
        red2 = 0;
        green1 = map(led, 0, nivelefeito2 - 1, 0, brilhomax);
        green2 = 0;
        blue1 = 0;
        blue2 = 0;
      } else {
        red1 = 0;
        red2 = map(led, nivelefeito2, brilhomax, 0, brilhomax);
        green1 = led;
        green2 = 0;
        blue1 = 0;
        blue2 = 0;
      }
    } else if (efeitoritmico == 3) {

    }
    maior = sensibilidade;
    tempomillis = millis() + attleds;
  }
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  red1 = red;
  green1 = green;
  blue1 = blue;

  red2 = red;
  green2 = green;
  blue2 = blue;
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

void Strobo() {
  if ((millis() - delaystrobo) < tempostrobo) {
    CorStatica(corstrobo, brilhomax);
  } else {
    red1 = 0;
    red2 = 0;
    green1 = 0;
    green2 = 0;
    blue1 = 0;
    blue2 = 0;
  }

  if ((millis() - delaystrobo) > (tempostrobo * 2)) {
    delaystrobo = millis();
  }
}

void CorStatica(int corcorstatica, int brilhomax) {
  if (corcorstatica == 0) {
    red1 = brilhomax;
    red2 = brilhomax;
    green1 = brilhomax;
    green2 = brilhomax;
    blue1 = brilhomax;
    blue2 = brilhomax;
  } else if (corcorstatica == 1) {
    red1 = brilhomax;
    red2 = brilhomax;
    green1 = 0;
    green2 = 0;
    blue1 = 0;
    blue2 = 0;
  } else if (corcorstatica == 2) {
    red1 = brilhomax;
    red2 = brilhomax;
    green1 = brilhomax;
    green2 = brilhomax;
    blue1 = 0;
    blue2 = 0;
  } else if (corcorstatica == 3) {
    red1 = 0;
    red2 = 0;
    green1 = brilhomax;
    green2 = brilhomax;
    blue1 = 0;
    blue2 = 0;
  } else if (corcorstatica == 4) {
    red1 = 0;
    red2 = 0;
    green1 = brilhomax;
    green2 = brilhomax;
    blue1 = brilhomax;
    blue2 = brilhomax;
  } else if (corcorstatica == 5) {
    red1 = 0;
    red2 = 0;
    green1 = 0;
    green2 = 0;
    blue1 = brilhomax;
    blue2 = brilhomax;
  } else if (corcorstatica == 6) {
    red1 = brilhomax;
    red2 = brilhomax;
    green1 = 0;
    green2 = 0;
    blue1 = brilhomax;
    blue2 = brilhomax;
  }
}

void FadeCoresUnica() {
  if (millis() - lasttimefadecorunica >= auxtempofadecorunica ) {
    if (brifadeunciobool) {
      brifadeuncio++;
    } else {
      brifadeuncio--;
    }
    if (brifadeuncio > luzmaxfadecorunica || brifadeuncio < 1) {
      if (brifadeuncio > luzmaxfadecorunica) {
        brifadeuncio = luzmaxfadecorunica;
      } else {
        brifadeuncio = 1;
      }
      brifadeunciobool = !brifadeunciobool;
    }
    lasttimefadecorunica = millis();
  }
  red1 = 0;
  red2 = 0;
  green1 = 0;
  green2 = 0;
  blue1 = brifadeuncio;
  blue2 = brifadeuncio;
  if (millis() >= fadecorunica) {
    fadecorunica += tempofadecorunica;
    auxtempofadecorunica = tempofadecorunica;
    auxtempofadecorunica = auxtempofadecorunica / luzmaxfadecorunica;
  }
}



void corrgb(int r, int g, int b) {
  red1 = r;
  red2 = r;
  green1 = g;
  green2 = g;
  blue1 = b;
  blue2 = b;
}

void corrgbcontrolada() {
  corrgb(corred, corgreen, corblue);
}

void Iniciado() {
  Botoes();
  switch (efeito) {
    case 0:
      if (millis() >= fade_goTime) Fade();
      break;
    case 1:
      Ritmico();
      break;
    case 2:
      Strobo();
      break;
    case 3:
      CorStatica(corstatica, brilhocorstatica);
      break;
    case 4:
      FadeCoresUnica();
      break;
    case 5:
      corrgbcontrolada();
      break;
  }
  luzligado = true;
}

void loop() {
  sound = analogRead(SOUND);
  botao = analogRead(BOTAO);
  ldr = analogRead(LDR);

  Botoes();
  if (ligado) {
    Iniciado();
  } else {
    Desligado();
  }

  analogWrite(GREEN1, green1);
  analogWrite(GREEN2, green2);
  analogWrite(BLUE1, blue1);
  analogWrite(BLUE2, blue2);
  analogWrite(RED1, red1);
  analogWrite(RED2, red2);
}
