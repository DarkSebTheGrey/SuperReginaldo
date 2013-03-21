//
//  Event.h
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __BaseEngine__Event__
#define __BaseEngine__Event__

#include <iostream>
#include "Data.h"

typedef enum EventType {
    LOADMAP,
    LOADLVL,
    SAVELVL,
    REFRESHCASE,
    P1LEFT,
    P1LEFTEND,
    P1RIGHT,
    P1RIGHTEND,
    P1UP,
    P1UPEND,
    P1DOWN,
    P1DOWNEND,
    P1ACTION1,
    P1ACTION1END,
    P1ACTION2,
    P1ACTION2END
} eventType;


class Event {
    eventType type;
    Data * d;
public:
    Event(eventType _type, Data *_d = 0):type(_type),d(_d) {}
    int getType(){
        return type;
    }
    Data* getData(){
        return d;
    }
};
#endif /* defined(__BaseEngine__Event__) */
