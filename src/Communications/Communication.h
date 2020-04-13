/**
 * @file Scaduino.h
 * @author Wesley José Santos (binary-quantum.com)
 * @brief Scaduino communication generic class
 * @version 0.1
 * @date 2020-04-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __COMMUNICATION__H__
#define __COMMUNICATION__H__

#include <stdio.h>
#include <ArduinoJson.h>
#include "Message.h"
#include "Data/Data.h"

class Communication
{
private:
    StaticJsonDocument<256> jsonDoc;
public:
    Communication();

    virtual void readRawData();
    virtual void sendRawData(String data);

    void parseData(String jsonString);

    Data *dataBase;
    uint16_t dataBaseSize;
    uint16_t deviceId;
};

Communication::Communication(){}

void Communication::readRawData(){
    //TODO: Override readRawData method to use a custom communication method
}

void Communication::sendRawData(String data){
    //TODO: Override sendRawData method to use a custom communication method
}

void Communication::parseData(String JsonString){
    Message msg = Message(JsonString);
    if(msg.deviceId != deviceId) return;
    switch (msg.type)
    {
    case MsgType::Status:
        
        break;
    case MsgType::Data:
        MsgData msgData(JsonString);
        this->dataBase[msgData.address].setData(msgData.data, msgData.dataType);
        break;
    case MsgType::Event:
        
        break;
    default:
        break;
    }
}

#endif  //!__COMMUNICATION__H__