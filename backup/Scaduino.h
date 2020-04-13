/**
 * @file Scaduino.h
 * @author Wesley José Santos (binary-quantum.com)
 * @brief Scaduino main class
 * @version 0.1
 * @date 2020-04-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __SCADUINO__H__
#define __SCADUINO__H__

#include <stdio.h>
#include "Communication/Communication.h"  
#include "Communication/CommunicationSerial.h"  

class Scaduino
{
private:
    Communication *communication;
public:
    void scaduinoTask();

    void sendByte(uint8_t byte, uint16_t address);
    //TODO: void sendWord(uint16_t word, uint16_t address);
    //TODO: void sendNumber(int number, uint16_t address);
    //TODO: void sendDecimal(float decimal, uint16_t address);
    //TODO: void sendString(String string, uint16_t address);
    //TODO: void sendJson(String json, uint16_t address);

    byte getByte(uint16_t address);
    //TODO: void getWord(uint16_t word, uint16_t address);
    //TODO: void getNumber(int number, uint16_t address);
    //TODO: void getDecimal(float decimal, uint16_t address);
    //TODO: void getString(String string, uint16_t address);
    //TODO: void getJson(String json, uint16_t address);
    Scaduino(Communication *communication);
};

void Scaduino::scaduinoTask(){
    communication->communicationTask();
}

Scaduino::Scaduino(Communication *communication){
    this->communication = communication;
}

void Scaduino::sendByte(uint8_t byte, uint16_t address){
    if(communication->data != NULL)
        communication->data[address] = byte;
}

byte Scaduino::getByte(uint16_t address){
    if(communication->data != NULL)
        return(communication->data[address]);
    else
        return(0);
}


#endif  //!__SCADUINO__H__