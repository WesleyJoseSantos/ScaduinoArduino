#include <Arduino.h>
#include "Scaduino.h"

Scaduino scdino;
ScaduinoBus scdBus(15);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  scdBus.setBus(&Serial);
  scdino.setCommunication(&scdBus);

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  scdino.scaduinoTask();

  bool pin12 = scdino.getTag<bool>(TagType::Boolean, 0);
  bool pin13 = scdino.getTag<bool>(TagType::Boolean, 1);

  digitalWrite(12, pin12);
  digitalWrite(13, pin13);
}