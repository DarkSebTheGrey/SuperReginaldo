//
//  Case.h
//  SuperReginaldo
//
//  Created by memo on 27/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __SuperReginaldo__Case__
#define __SuperReginaldo__Case__

#include <iostream>

#define GRASS 0
#define IRON 1
#define ROCK 2
#define BRICKORANGE 3
#define BRICKGREY 4
#define INTERPOINT 5

class Case {
    
public:
    int posX,posY;
    int type;
    Case(int _posX,int _posY = 0,int _type = 0):posX(_posX),posY(_posY),type(_type){}
    
};
#endif /* defined(__SuperReginaldo__Case__) */
