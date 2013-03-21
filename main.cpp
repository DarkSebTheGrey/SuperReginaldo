//
//  main.cpp
//  SuperReginaldo
//
//  Created by memo on 26/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include <iostream>
#include "GraphicEngine.h"
#include "GameEngine.h"


#include <sstream>
#include <cstdarg>
#include <cerrno>

#include "Md2Entity.h"
#include "TextureManager.h"

#include <algorithm>
#include "Stopwatch.h"
#include "enums.h"
#include "Animable.h"


int main(int argc, char * argv[])
{
    GraphicEngine graphicEngine(argc,argv);
    GameEngine gameEngine;
    gameEngine.start();
    Engine::sendEvent(new Event(LOADLVL));
    Engine::seekEvent();
    graphicEngine.start();
    
    return 0;
}

