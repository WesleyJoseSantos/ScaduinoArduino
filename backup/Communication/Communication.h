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

enum ErrCode{
    ERR_COMM_OK=0,
    ERR_COMM_SEQUENCE,
};

class Communication
{
private:

    enum GeneralState
    {
        ST_GENERAL_TURNED_ON=0,
        ST_GENERAL_DATA_READ_COMPLETE,
        ST_GENERAL_DATA_SEND_COMPLETE,
    };

    enum DataCycleState
    {
        ST_DATA_CYCLE_TURNED_ON=0,
        ST_DATA_CYCLE_START_CODE_HANDLED,
        ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED,
        ST_DATA_CYCLE_END,
    };

    GeneralState generalState;
    DataCycleState readDataState;
    DataCycleState sendDataState;

    uint16_t size;
    uint16_t dataIdx;
    uint8_t startCode;
    ErrCode errCode;
    bool sizeByte0;

    void readData(uint8_t data);
    int sendData();
    
public:
    Communication(uint8_t startCode);
    int dataExchangeTask(int data);
    virtual void communicationTask();
    uint8_t *data;
};

Communication::Communication(uint8_t startCode){
    generalState = ST_GENERAL_TURNED_ON;
    readDataState = ST_DATA_CYCLE_TURNED_ON;
    sendDataState = ST_DATA_CYCLE_TURNED_ON;
    this->startCode = startCode;
    errCode = ERR_COMM_OK;
    dataIdx = 0;
    sizeByte0 = false;
}

int Communication::dataExchangeTask(int data){
    int ret = -1;
    switch (generalState)
    {
    case ST_GENERAL_TURNED_ON:
        if(data != -1) readData((uint8_t)data);
        if(readDataState == ST_DATA_CYCLE_END && dataIdx == 0) 
            generalState = ST_GENERAL_DATA_READ_COMPLETE;
        break;
    case ST_GENERAL_DATA_READ_COMPLETE:
        //Serial.println("ST_GENERAL_DATA_READ_COMPLETE");
        ret = sendData();
        if(sendDataState == ST_DATA_CYCLE_END  && dataIdx == 0)
            generalState = ST_GENERAL_DATA_SEND_COMPLETE;
        break;
    case ST_GENERAL_DATA_SEND_COMPLETE:
        //Serial.println("ST_GENERAL_DATA_SEND_COMPLETE");
        generalState = ST_GENERAL_TURNED_ON;
        sendDataState = ST_DATA_CYCLE_TURNED_ON;
        readDataState = ST_DATA_CYCLE_TURNED_ON;
        break;
    default:
        break;
    }
    return(ret);
}

void Communication::readData(uint8_t data){
    switch (readDataState)
    {
    case ST_DATA_CYCLE_TURNED_ON:
        //Serial.println("dataRead -> ST_DATA_CYCLE_TURNED_ON");
        if(data == startCode)
            readDataState = ST_DATA_CYCLE_START_CODE_HANDLED;
        break;
    case ST_DATA_CYCLE_START_CODE_HANDLED:
        //Serial.println("dataRead -> ST_DATA_CYCLE_START_CODE_HANDLED");
        if(this->data != NULL){
            readDataState = ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED;
            break;
        }
        if(sizeByte0 == false){
            sizeByte0 = true;
            size = data;
        }else{
            sizeByte0 = false;
            size |= data << 8;
            this->data = (uint8_t*) malloc(size * sizeof(uint8_t));
            for (size_t i = 0; i < size; i++)
            {
                this->data[i] = 0;
            }
            readDataState = ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED;
        }
        break;
    case ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED:
        //Serial.println("dataRead -> ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED");
        // if(this->data[dataIdx] == 0)
            this->data[dataIdx] = data;
        dataIdx++;
        if(dataIdx == size) readDataState = ST_DATA_CYCLE_END;
        break;
    case ST_DATA_CYCLE_END:
        //Serial.println("dataRead -> ST_DATA_CYCLE_END");
        dataIdx = 0;
        break;
    default:
        break;
    }
}

int Communication::sendData(){
    switch (sendDataState)
    {
    case ST_DATA_CYCLE_TURNED_ON:
        //Serial.println("sendData -> ST_DATA_CYCLE_TURNED_ON");
        sendDataState = ST_DATA_CYCLE_START_CODE_HANDLED;
        return(startCode);
        break;
    case ST_DATA_CYCLE_START_CODE_HANDLED:
        //Serial.println("sendData -> ST_DATA_CYCLE_START_CODE_HANDLED");
        if(sizeByte0 == false){
            sizeByte0 = true;
            return((uint8_t)size);
        }else{
            sendDataState = ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED;
            sizeByte0 = false;
            return((uint8_t)size >> 8);
        }
        break;
    case ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED:
        // Serial.print("sendData -> ST_DATA_CYCLE_MESSAGE_SIZE_HANDLED ");
        // Serial.print(dataIdx);
        // Serial.print(" - ");
        //Serial.println(size);
        if(dataIdx == size - 1){
            sendDataState = ST_DATA_CYCLE_END;
        }
        dataIdx++;
        return(this->data[dataIdx - 1]);
        break;
    case ST_DATA_CYCLE_END:
        //Serial.println("sendData -> ST_DATA_CYCLE_END");
        dataIdx = 0;
        return(-1);
        break;
    default:
        return(-1);
        break;
    }
    return(-1);
}

#endif  //!__COMMUNICATION__H__