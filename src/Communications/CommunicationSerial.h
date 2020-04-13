/**
 * @file Scaduino.h
 * @author Wesley José Santos (binary-quantum.com)
 * @brief Scaduino communication serial class
 * @version 0.1
 * @date 2020-04-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __COMMUNICATIONSERIAL__H__
#define __COMMUNICATIONSERIAL__H__

#include <Stream.h>
#include "Communication.h"

class CommunicationSerial: public Communication
{
private:
    Stream *stream;
    void readRawData() override;
    void sendRawData(String data) override;
public:
    CommunicationSerial();
    void setSerial(Stream *stream);
};

CommunicationSerial::CommunicationSerial(){
    this->deviceId = 1;
}

void CommunicationSerial::readRawData(){
    if(stream->available()){
        String data = stream->readStringUntil('\n');
        parseData(data);
    }
}

void CommunicationSerial::sendRawData(String data){
    stream->println(data);
}

void CommunicationSerial::setSerial(Stream *stream){
    this->stream = stream;
}

#endif  //!__COMMUNICATIONSERIAL__H__