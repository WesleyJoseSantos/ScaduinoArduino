/**
 * @file ScaduinoBus.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-05-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __SCADUINOBUS__H__
#define __SCADUINOBUS__H__

#include <Stream.h>
#include "Communication.h"

class ScaduinoBus : public Communication
{
private:
    Stream *bus;
    
    enum State
    {
        ST_TURNED_ON=0,
        ST_LAST_TAG_RECIEVED,
        ST_LAST_TAG_SENDED
    };

    void processData(String data);

    State state;
    TagData tagData;
    uint16_t idx;
    char separatorChar, endChar;
public:
    ScaduinoBus(size_t size, char separatorChar = ',', char endChar = '\n', uint16_t deviceId = 1);
    void communicationTask() override;
    void setBus(Stream *bus);
};

ScaduinoBus::ScaduinoBus(size_t size, char separatorChar = ',', char endChar = '\n', uint16_t deviceId = 1)
{
    this->deviceId = deviceId;
    this->separatorChar = separatorChar;
    this->endChar = endChar;
    this->tagsCount = size;
    if(this->tags != 0)    {
        delete [] this->tags;
    }
    this->tags = new Tag [size];
    for(size_t i = 0; i < size; i++){
        tags[i].setData((int16_t)0);
        tags[i].checkTagChanged();
    }
}

void ScaduinoBus::setBus(Stream *bus){
    this->bus = bus;
}

void ScaduinoBus::communicationTask(){
    if (bus->available()){
        String data;
        if (idx < tagsCount - 1){
            data = bus->readStringUntil(separatorChar);
        }else{
            data = bus->readStringUntil(endChar);
        }
        processData(data);
    }
}

void ScaduinoBus::processData(String data){
    if(!tags[idx].checkTagChanged()){
        tags[idx].setData(data);
        tags[idx].checkTagChanged();
    }
    bus->print(tags[idx].getData<String>(TagType::String));
    bus->print(separatorChar);
    idx++;
    if(idx == tagsCount){
        bus->print(endChar);
        idx = 0;
    }
}

#endif  //!__SCADUINOBUS__H__