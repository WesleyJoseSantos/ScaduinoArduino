#include <Arduino.h>
#include "Scaduino.h"

CommunicationSerial communication;
Scaduino scaduino = Scaduino(&communication);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  communication.setSerial(&Serial);
  scaduino.start();
  scaduino.createDataBase(10);
}

void loop(){
  scaduino.task();
}