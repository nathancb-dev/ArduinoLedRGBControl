#include <SPI.h>
#include <LiquidCrystal.h>
#include <Ethernet.h>
//#include <SD.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 150); // Endereço IP que a Ethernet Shield terá. Deve ser alterado para um endereço livre da sua rede.
EthernetServer server(80);     // Cria um servidor WEB
LiquidCrystal lcd(39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49); //inicial o objeto LCD

//LCD variaveis
#define PContrasteLCD 2

#define BT1 22
#define BT2 23
#define BT3 25

// Fita Led variaveis
#define RED1 5
#define RED2 9

#define GREEN1 4
#define GREEN2 8

#define BLUE1 3
#define BLUE2 7


void initTop() {
  pinMode(2, OUTPUT); // contraste LCD

  pinMode(BT1, INPUT_PULLUP); // bt 1
  pinMode(BT2, INPUT_PULLUP); // bt 2
  pinMode(BT3, INPUT_PULLUP); // bt 3

  Serial.begin(9600);
}
