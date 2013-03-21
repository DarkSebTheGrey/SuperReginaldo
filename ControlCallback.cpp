//
//  ControlCallback.cpp
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "ControlCallback.h"

int typeCase = 0;

//glutKeyboardFunc() et glutKeyboardUpFunc() pour le relachement de la touche
void KeyboardCallback(unsigned char key,int x, int y){
    switch (key) {
        case 'z':
            Engine::sendEvent(new Event(P1UP));
            Engine::seekEvent();
            break;
        case 's':
            Engine::sendEvent(new Event(P1DOWN));
            Engine::seekEvent();
            break;
        case 'd':
            Engine::sendEvent(new Event(P1RIGHT));
            Engine::seekEvent();
            break;
        case 'q':
            Engine::sendEvent(new Event(P1LEFT));
            Engine::seekEvent();
            break;
        case 'k':
            Engine::sendEvent(new Event(P1ACTION1));
            Engine::seekEvent();
            break;
        case 'o':
            Engine::sendEvent(new Event(P1ACTION2));
            Engine::seekEvent();
            break;
        case 'a':
            SharedData::eyeZ += 1.0;
            SharedData::centerZ += 1.0;
            break;
        case 'e':
            SharedData::eyeZ -= 1.0;
            SharedData::centerZ -= 1.0;
            break;
        case 'l':
            Engine::sendEvent(new Event(LOADLVL));
            Engine::seekEvent();
            break;
        case 'i':
            Engine::sendEvent(new Event(SAVELVL));
            Engine::seekEvent();
            break;
        case 'f':
            SharedData::fpsAffichage = ! SharedData::fpsAffichage;
            break;
        case 'p':
            exit(0);
            break;
        case 'g':
            SharedData::persos[0]->setAnim(AnimEnum::R_DOUBLEJUMP);
            SharedData::persos[0]->setTexture(1);
            
            break;
        case '1':
            typeCase = 0;
            break;
        case '2':
            typeCase = 1;
            break;
        case '3':
            typeCase = 2;
            break;
        case '4':
            typeCase = 3;
            break;
        case '5':
            typeCase = 4;
            break;
        case '6':
            typeCase = 5;
            break;
        default:
            break;
    }
}
void KeyboardReleaseCallback(unsigned char key,int x, int y){
    switch (key) {
        case 'z':
            Engine::sendEvent(new Event(P1UPEND));
            Engine::seekEvent();
            break;
        case 's':
            Engine::sendEvent(new Event(P1DOWNEND));
            Engine::seekEvent();
            break;
        case 'd':
            Engine::sendEvent(new Event(P1RIGHTEND));
            Engine::seekEvent();
            break;
        case 'q':
            Engine::sendEvent(new Event(P1LEFTEND));
            Engine::seekEvent();
            break;
        case 'k':
            Engine::sendEvent(new Event(P1ACTION1END));
            Engine::seekEvent();
            break;
        case 'o':
            Engine::sendEvent(new Event(P1ACTION2END));
            Engine::seekEvent();
            break;
        case 'p':
            exit(0);
            break;
        default:
            break;
    }
}
void specialCallback(int key,int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            SharedData::eyeY += 2.0;
            SharedData::centerY += 2.0;
            break;
        case GLUT_KEY_DOWN:
            SharedData::eyeY -= 2.0;
            SharedData::centerY -= 2.0;
            break;
        case GLUT_KEY_RIGHT:
            SharedData::eyeX += 2.0;
            SharedData::centerX += 2.0;
            break;
        case GLUT_KEY_LEFT:
            if (SharedData::eyeX > 8.0) {
                SharedData::eyeX -= 2.0;
                SharedData::centerX -= 2.0;
            }
            break;
            
        default:
            break;
    }
}

void MouseCallback(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int _x,_y;
        //6.40 pour avoir le pourcentage du clic
        // on divise par 100/8 et 100/6 car on a 8 cube en longueur et 6 en largeur, a modifier si plus de cube
        // le SharedData::eyeX -7 et car on retire la valeur pour laquel on a le premier cube tout a gauche
        _x = (x / 6.40) / (100/8.0) + SharedData::eyeX / 2 - 3;
        _y = (y / 4.80) / (100/6.0);
        _y = 5 - _y + SharedData::eyeY / 2 - 2;
        
        while (SharedData::Cases->size() <= _x) {
            SharedData::Cases->push_back(new std::vector<Case *>());
        }
        bool erase = false;
        for (int i = 0; i < (*SharedData::Cases)[_x]->size(); i++) {
            if (_y == (*(*SharedData::Cases)[_x])[i]->posY) {
                //case deja presente donc la suprimmer
                
                delete (*(*SharedData::Cases)[_x])[i];
                (*(*SharedData::Cases)[_x])[i] = (*(*SharedData::Cases)[_x])[(*(*SharedData::Cases)[_x]).size() - 1];
                (*(*SharedData::Cases)[_x]).pop_back();
                SharedData::nbCases --;
                erase = true;
            }
        }
        
        if (!erase) {
            (*SharedData::Cases)[_x]->push_back(new Case(_x,_y,typeCase));
            SharedData::nbCases ++;
        }
        Engine::sendEvent(new Event(REFRESHCASE));
        Engine::seekEvent();
    }
}

void MotionCallback(int x, int y){
    
}

void PassiveMotionCallback(int x, int y){
    
}