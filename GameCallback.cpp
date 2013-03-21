//
//  GameCallback.cpp
//  SuperReginaldo
//
//  Created by memo on 27/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "GameCallback.h"

void IdleCallback(void)
{
    SharedData::gameControlSwatch.stop();
    if (SharedData::gameControlSwatch.elapsed_ms() > 16)  //on block a 60 la framerate
    {
        SharedData::gameControlSwatch.start();
        //tout les 60eme de seconde:
        //checkEtat();                  -> dataEngine
        //Deplacables.deplace();        -> gameEngine
        SharedData::persos[0]->deplace();

        SharedData::persos[0]->anim();

        //Animable.anim();              -> GraphicEngine
        //Affichable.affiche();         -> GraphicEngine -> dans grapchicCallback
        glutPostRedisplay();            //-> GraphicEngine
        //Persos.testColision()         -> GameEngine

    }
}
