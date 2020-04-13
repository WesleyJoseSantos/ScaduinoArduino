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
#include "Components/Components.h"
#include "Communications/Communications.h"  

class Scaduino
{
private:
    Communication *communication;
public:
    Scaduino(Communication *communication);

    void start();
    void task();
    void showStatus(bool show);
    void showErrors(bool show);

    void createDataBase(uint16_t size){
        this->communication->dataBase = (Data*) malloc(size * sizeof(Data));
        if(this->communication->dataBase == NULL){
            //TODO: Send error status
        }else{
            communication->dataBaseSize = size;
        }
    }

    void sendBool(bool boolean, uint16_t address);
    void sendByte(uint8_t byte, uint16_t address);
    void sendWord(uint16_t word, uint16_t address);
    void sendNumber(int number, uint16_t address);
    void sendDecimal(float decimal, uint16_t address);
    //TODO: void sendString(String string, uint16_t address);
    //TODO: void sendJson(String json, uint16_t address);

    bool getBool(uint16_t address);
    byte getByte(uint16_t address);
    uint16_t getWord(uint16_t address);
    int16_t getNumber(uint16_t address);
    float getDecimal(uint16_t address);
    //TODO: void getString(String string, uint16_t address);
    //TODO: void getJson(String json, uint16_t address);
};

Scaduino::Scaduino(Communication *communication){
    this->communication = communication;
}

void Scaduino::start(){
    //TODO: Send Start Status
}

void Scaduino::task(){
    communication->readRawData();
}

void Scaduino::sendBool(bool boolean, uint16_t address){

}

void Scaduino::sendByte(uint8_t byte, uint16_t address){

}

void Scaduino::sendWord(uint16_t word, uint16_t address){

}

void Scaduino::sendNumber(int number, uint16_t address){

}

void Scaduino::sendDecimal(float decimal, uint16_t address){

}

bool Scaduino::getBool(uint16_t address){
    if(address >= communication->dataBaseSize)
        //TODO: Send error status
    return communication->dataBase[address].getBool();    
}

byte Scaduino::getByte(uint16_t address){
    if(address >= communication->dataBaseSize)
        //TODO: Send error status
    return communication->dataBase[address].getByte();    
}

uint16_t Scaduino::getWord(uint16_t address){
    if(address >= communication->dataBaseSize)
        //TODO: Send error status
    return communication->dataBase[address].getWord();    
}

int16_t Scaduino::getNumber(uint16_t address){
    if(address >= communication->dataBaseSize)
        //TODO: Send error status
    return communication->dataBase[address].getNumber();    
}

float Scaduino::getDecimal(uint16_t address){
    if(address >= communication->dataBaseSize)
        //TODO: Send error status
    return communication->dataBase[address].getDecimal();    
}


#endif  //!__SCADUINO__H__