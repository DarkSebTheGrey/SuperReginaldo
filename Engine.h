//
//  Engine.h
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __BaseEngine__Engine__
#define __BaseEngine__Engine__

#include <iostream>
#include <queue>
#include <vector>
#include "Event.h"

class Engine {
    static std::vector<Engine *> instances;
    std::queue<Event*> fileEvent;
protected:
    virtual void processEvent() = 0;
    
    bool hasNextEvent(){
        return ! fileEvent.empty();
    }
    
    Event * getNextEvent(){
        Event * e =  fileEvent.front();
        fileEvent.pop();
        return e;
    }
public:
    Engine(){
        instances.push_back(this);
    }
    static void sendEvent(Event *e){
        for (int i=0; i < instances.size(); i++) {
            instances[i]->addEvent(e);
        }
    }
    static void seekEvent(){
        for (int i=0; i < instances.size(); i++) {
            instances[i]->processEvent();
        }

    }
    
    void addEvent(Event *e){
        fileEvent.push(e);
    }
    virtual void start() = 0;
};

#endif /* defined(__BaseEngine__Engine__) */
