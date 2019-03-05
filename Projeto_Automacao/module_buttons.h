Button button1(7);
void invertPort(int outPort){
  digitalWrite(outPort, !digitalRead(outPort));
}

void buttonInvertOutput(Button *bt, int outPort){
  bt->read();
  if (bt->wasPressed() || bt->wasReleased()) {
    invertPort(outPort);
  }
}

void verifyButtons(){
  buttonInvertOutput(&button1, 8);
}

void init_buttons(){
  button1.begin();
  pinMode(8, OUTPUT);
}
