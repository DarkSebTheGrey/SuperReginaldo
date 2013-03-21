//
//  Reginaldo.h
//  SuperReginaldo
//
//  Created by memo on 01/03/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __SuperReginaldo__Reginaldo__
#define __SuperReginaldo__Reginaldo__

#include <iostream>
#include "Perso.h"
#include "SharedData.h"

#include "GLUT.h"

class Reginaldo:public Perso {
    float rot;
    float posX,posY;
    float vitX,vitY;
    float scale;
    bool direction;
public:
    Reginaldo():rot(270.0f),posX(6.0f),posY(1.0f),scale(0.0015f),vitX(0.0),vitY(0.0),direction(true),Perso(SharedData::REGINALDO_E, AnimEnum::R_NOMOVE, 0){

    }
    ~Reginaldo(){}
    void testColision();

    void deplace();

    void affiche(){

        double topx1 = (direction)?boxRight()->topleftx*scale:boxLeft()->topleftx*scale;
        double topy1 = (direction)?boxRight()->toplefty*scale:boxLeft()->toplefty*scale;
        double botx1 = (direction)?boxRight()->bottomrightx*scale:boxLeft()->bottomrightx*scale;
        double boty1 = (direction)?boxRight()->bottomrighty*scale:boxLeft()->bottomrighty*scale;

        glPushMatrix();
        glBegin (GL_LINES);

        glColor3f (1.0,1.0,1.0);
        glVertex3f (posX+ topx1,posY + topy1,0);
        glVertex3f (posX + botx1,posY + topy1,0);
        glVertex3f (posX + topx1,posY + topy1,0);
        glVertex3f (posX + topx1,posY + boty1,0);
        glVertex3f (posX + topx1,posY + boty1,0);
        glVertex3f (posX + botx1,posY + boty1,0);
        glVertex3f (posX + botx1,posY + topy1,0);
        glVertex3f (posX + botx1,posY + boty1,0);
        glVertex3f (posX,posY + topy1,0);
        glVertex3f (posX,posY + boty1,0);
        glVertex3f (posX + topx1,posY,0);
        glVertex3f (posX + botx1,posY,0);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(posX, posY, 0.0f);
        glRotatef(rot, 0.0f, 1.0f, 0.0f);
        glScalef(scale,scale,scale);
        Perso::affiche();

        glPopMatrix();
    }

    void left();
    void leftEnd();
    void right();
    void rightEnd();
    void up();
    void upEnd();
    void down();
    void downEnd();
    void action1();
    void action1End();
    void action2();
    void action2End();

};
#endif /* defined(__SuperReginaldo__Reginaldo__) */
