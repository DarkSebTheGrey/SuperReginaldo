//
//  Perso.h
//  SuperReginaldo
//
//  Created by memo on 26/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __SuperReginaldo__Perso__
#define __SuperReginaldo__Perso__

#include <iostream>
#include "Animable.h"
#include "Deplacable.h"

class Perso:public Animable,public Deplacable{
protected:
    int currentTextur;
    int mode;
    
public:
    Perso(Md2Entity *entity, anim_t defaultAnim, int defaultSkin):Animable(entity,defaultAnim,defaultSkin){}
    ~Perso();
    virtual void testColision() = 0;
    
    //primitive de control
    virtual void left() = 0;
    virtual void leftEnd() = 0;
    virtual void right() = 0;
    virtual void rightEnd() = 0;
    virtual void up() = 0;
    virtual void upEnd() = 0;
    virtual void down() = 0;
    virtual void downEnd() = 0;
    virtual void action1() = 0;
    virtual void action1End() = 0;
    virtual void action2() = 0;
    virtual void action2End() = 0;
    
};
#endif /* defined(__SuperReginaldo__Perso__) */
