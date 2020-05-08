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
#include "Communication\Communications.h"  

class Scaduino
{
private:
    Communication *communication;
public:
    Scaduino();
    
    void setCommunication(Communication *communication);
    void scaduinoTask();

    void setTag(bool value, uint16_t address);
    void setTag(int16_t value, uint16_t address);
    void setTag(float value, uint16_t address);
    void setTag(String value, uint16_t address);

    template <typename T>
    T getTag(TagType type, uint16_t address);
};

Scaduino::Scaduino(){

}

void Scaduino::scaduinoTask(){
    communication->communicationTask();
}

void Scaduino::setCommunication(Communication *communication){
    this->communication = communication;
}

template <typename T>
T Scaduino::getTag(TagType type, uint16_t address){
    return(communication->tags[address].getData<T>(type));
}

void Scaduino::setTag(bool value, uint16_t address){
    communication->tags[address].setData(value);
}

void Scaduino::setTag(int16_t value, uint16_t address){
    communication->tags[address].setData(value);
}

void Scaduino::setTag(float value, uint16_t address){
    communication->tags[address].setData(value);
}

void Scaduino::setTag(String value, uint16_t address){
    communication->tags[address].setData(value);
}


#endif  //!__SCADUINO__H__