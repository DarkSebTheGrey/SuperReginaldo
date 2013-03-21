//
//  ControlCallback.h
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __BaseEngine__ControlCallback__
#define __BaseEngine__ControlCallback__

#include <iostream>
#include "SharedData.h"
#include "Engine.h"
#include "GameEngine.h"

void KeyboardCallback(unsigned char key,int x, int y);

void KeyboardReleaseCallback(unsigned char key,int x, int y);

void specialCallback(int key,int x, int y);

void MouseCallback(int button, int state, int x, int y);

void MotionCallback(int x, int y);

void PassiveMotionCallback(int x, int y);

#endif /* defined(__BaseEngine__ControlCallback__) */
