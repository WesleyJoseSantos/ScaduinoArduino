/**
 * @file DataType.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __DATATYPE__H__
#define __DATATYPE__H__

#include <WString.h>

union DynamicData
{
    bool boolean;
    uint8_t byte;
    uint16_t word;
    int16_t number;
    float decimal;
};

class DataType
{
    public:
    enum Type
    {
        Boolean,
        Byte,
        Word,
        Number,
        Decimal,
    };
    
    Type type;
};

class Data
{
public:
    Data();

    Data(bool boolean){this->data.boolean = boolean;}
    Data(uint8_t byte){this->data.byte = byte;}
    Data(uint16_t word){this->data.word = word;}
    Data(int16_t number){this->data.number = number;}
    Data(float decimal){this->data.decimal = decimal;}

    int getData();
    void setData(DynamicData data, uint8_t type);

    bool getBool(){return this->data.boolean;}
    uint8_t getByte(){return this->data.byte;}
    uint16_t getWord(){return this->data.word;}
    int16_t getNumber(){return this->data.number;}
    float getDecimal(){return this->data.decimal;}
private:

    DynamicData data;
    DataType::Type type;
};

Data::Data(){

}

void Data::setData(DynamicData data, uint8_t type){
    this->type = (DataType::Type)type;
    switch (type)
    {
    case DataType::Boolean:
        this->data.boolean = data.boolean;
        break;
    case DataType::Byte:
        this->data.byte = data.byte;
        break;
    case DataType::Word:
        this->data.word = data.word;
        break;
    case DataType::Number:
        this->data.number = data.number;
        break;
    case DataType::Decimal:
        this->data.decimal = data.decimal;
        break;
    default:
        break;
    }
}

#endif  //!__DATATYPE__H__