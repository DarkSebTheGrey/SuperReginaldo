//
//  GameEngine.h
//  SuperReginaldo
//
//  Created by memo on 27/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __SuperReginaldo__GameEngine__
#define __SuperReginaldo__GameEngine__

#define tailleBlock 2.0
#define tailleBlockSurDeux tailleBlock / 2.0


#include <iostream>
#include "Engine.h"
#include "SharedData.h"
#include <fstream>

#include "Reginaldo.h"

class GameEngine:public Engine {
    std::ifstream *f;
    std::ofstream *of;

    void loadLvl();
    void saveLvl();
    void makeLvlArrays();

    void addCases(Case *c);


public:


    void start(){
        SharedData::gameControlSwatch.start();

        //on creer le perso 1 qui sera utiliser tout au long du jeu
        SharedData::persos.push_back(new Reginaldo());
    }

    void processEvent();


};

#endif /* defined(__SuperReginaldo__GameEngine__) */
