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
public:
    CommunicationSerial(uint8_t startCode);
    void communicationTask() override;
    void setSerial(Stream *stream);
};

CommunicationSerial::CommunicationSerial(uint8_t startCode):
Communication(startCode){
    
}

void CommunicationSerial::communicationTask(){
    int ret = dataExchangeTask(stream->read());
    if(ret >= 0){
        uint8_t data = (uint8_t)ret;
        stream->write(data);
    }
}

void CommunicationSerial::setSerial(Stream *stream){
    this->stream = stream;
}

#endif  //!__COMMUNICATIONSERIAL__H__