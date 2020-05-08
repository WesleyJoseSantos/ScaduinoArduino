/**
 * @file Communication.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-05-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __COMMUNICATION__H__
#define __COMMUNICATION__H__

#include "..\Tag\Tag.h"

//TODO: implement or use communcation libs to create custom classes that inherits this communication class
class Communication
{
private:
    
public:
    Communication();
    virtual void communicationTask();

    Tag *tags;
    uint16_t tagsCount;
    uint16_t deviceId;
};

Communication::Communication()
{
}

void Communication::communicationTask(){
    //TODO: override this method to implement communication operations for a custom data exchange protocol, handling this->tags values
}

#endif  //!__COMMUNICATION__H__