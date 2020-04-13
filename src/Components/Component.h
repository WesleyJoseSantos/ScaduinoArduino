/**
 * @file Component.h
 * @author Wesley José Santos (binary-quantum.com)
 * @brief An generic component class header file
 * @version 0.1
 * @date 2020-04-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __COMPONENT__H__
#define __COMPONENT__H__

#include <stdio.h>
#include "Event.h"

class Component
{
private:
    
public:
    Component();
    uint16_t componentId;
    Event *events;
};

Component::Component()
{
}

#endif  //!__COMPONENT__H__