/**
 * @file Message.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __MESSAGE__H__
#define __MESSAGE__H__

#include <ArduinoJson.h>
#include "Data\Data.h"

class MsgType{
public:
    enum
    {
        Status,
        Data,
        Event
    };  
};

class Message{
public:
    uint8_t type;
    uint16_t deviceId;

    Message(){}

    Message(String jsonString){
        StaticJsonDocument<64> doc;
        deserializeJson(doc, jsonString);
        type = doc["type"];
        deviceId = doc["deviceId"];
    }

};

class MsgStatus:public Message{
public:
    enum StatusCodes{
        AdressOutOfRange=-2,
        DataBaseError,
        Ok,
        Start
    };
    uint16_t code;

    MsgStatus(String jsonString){
        StaticJsonDocument<64> doc;
        deserializeJson(doc, jsonString);
        code = doc["code"];
    }
};

class MsgData:public Message{
public:
    DynamicData data;
    uint8_t dataType;
    uint16_t address;

    MsgData(String jsonString){
        StaticJsonDocument<64> doc;
        deserializeJson(doc, jsonString);
        dataType = doc["dataType"];
        switch (dataType)
        {
        case DataType::Boolean:
            data.boolean = doc["data"];
            break;
        case DataType::Byte:
            data.byte = doc["data"];
            break;
        case DataType::Word:
            data.word = doc["data"];
            break;
        case DataType::Number:
            data.number = doc["data"];
            break;
        case DataType::Decimal:
            data.decimal = doc["data"];
            break;
        default:
            break;
        }
        address = doc["address"];
    }
};

class MsgEvent:public Message{
public:
    uint16_t componentId;
    uint16_t eventId;

    MsgEvent(String jsonString){
        StaticJsonDocument<64> doc;
        deserializeJson(doc, jsonString);
        componentId = doc["componentId"];
        eventId = doc["eventId"];
    }
};

#endif  //!__MESSAGEH__H__