/**
 * @file Tag.h
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

enum class TagType
{
    Boolean,
    Integer,
    Float,
    String
};

class TagData
{
public:
    bool booleanValue;
    int16_t integerValue;
    float floatValue;
    String stringValue;

    TagData(){
       booleanValue = false;
       integerValue = 0;
       floatValue = 0;
       stringValue = ""; 
    }

};

class Tag
{
public:
    Tag();
    void setData(TagData data);
    void setData(bool booleanValue);
    void setData(int16_t integerValue);
    void setData(float floatValue);
    void setData(String stringValue);

    template <typename T>
    T getData(TagType type);

    bool checkTagChanged();
private:

    bool tagChanged;
    TagData data;
    TagType type;
};

Tag::Tag(){
    tagChanged = false;
}

void Tag::setData(TagData data){
    this->data.booleanValue = data.booleanValue;
    this->data.floatValue = data.floatValue;
    this->data.integerValue = data.integerValue;
    this->data.stringValue = data.stringValue;
    tagChanged = true;
}

void Tag::setData(bool booleanValue){
    this->data.booleanValue = booleanValue;
    this->data.integerValue = booleanValue;
    this->data.floatValue = booleanValue;
    this->data.stringValue = booleanValue;
    tagChanged = true;
}

void Tag::setData(int16_t integerValue){
    this->data.booleanValue = integerValue;
    this->data.integerValue = integerValue;
    this->data.floatValue = integerValue;
    this->data.stringValue = integerValue;
    tagChanged = true;
}

void Tag::setData(float floatValue){
    this->data.booleanValue = floatValue;
    this->data.integerValue = floatValue;
    this->data.floatValue = floatValue;
    this->data.stringValue = floatValue;
    tagChanged = true;
}

void Tag::setData(String stringValue){
    this->data.booleanValue = stringValue == "true";
    this->data.integerValue = stringValue.toInt();
    this->data.floatValue = stringValue.toFloat();
    this->data.stringValue = stringValue;
    tagChanged = true;
}

template <typename T>
T Tag::getData(TagType type){
    T value;
    switch (type)
    {
    case TagType::Boolean:
        value = (T)this->data.booleanValue;
        break;
    case TagType::Integer:
        value = (T)this->data.integerValue;
        break;
    case TagType::Float:
        value = (T)this->data.floatValue;
        break;
    case TagType::String:
        value = (T)this->data.stringValue;
        break;
    default:
        break;
    }
    return(value);
}

bool Tag::checkTagChanged(){
    bool ret = tagChanged;
    tagChanged = false;
    return(ret);
}

#endif  //!__DATATYPE__H__