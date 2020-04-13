/**
 * @file Event.h
 * @author Wesley José Santos (binary_quantum.com)
 * @brief An event generic class header file
 * @version 0.1
 * @date 2020-04-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __EVENT__H__
#define __EVENT__H__

#include <stdio.h>

class Event
{
private:
    
public:
    uint8_t eventId;
    virtual void action();
    Event();
};

Event::Event()
{
}

#endif  //!__EVENT__H__