//
//  Reginaldo.cpp
//  SuperReginaldo
//
//  Created by memo on 01/03/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "Reginaldo.h"
#include <math.h>

void Reginaldo::testColision(){}

void Reginaldo::deplace(){
    
    
    
    
    double topx = (direction)?boxRight()->topleftx*scale:boxLeft()->topleftx*scale;
    double topy = (direction)?boxRight()->toplefty*scale:boxLeft()->toplefty*scale;
    double botx = (direction)?boxRight()->bottomrightx*scale:boxLeft()->bottomrightx*scale;
    double boty = (direction)?boxRight()->bottomrighty*scale:boxLeft()->bottomrighty*scale;
    
    //test du sol:
    //si on est sur une ligne
    int indice = (posX + 1.0f)/2.0f;
    
    int indiceg = ((posX + topx + 1.0f)/2.0f);
    
    int indiced = ((posX + botx + 1.0f)/2.0f);
    
    
    
    bool doitDescendre = false;
    
    if (fmod(posY + 1.0f,2) > 0.1f) {
        doitDescendre = true;
    }else{
        doitDescendre = true;
//        int xmin = floor((posX + botx) / 2);
//        int xmax = ceil((posX + topx) / 2);
        int ymin = floor((posY + boty) / 2);
        for (int i = indiceg; i <= indiced; i++) {
            for (int j = 0; j < (*SharedData::Cases)[i]->size(); j++) {
                if (ymin == (*(*SharedData::Cases)[i])[j]->posY) {
                    doitDescendre = false;
                }
            }
        }
    }
    
    if (doitDescendre) {
        vitY -= 0.02f;
        if (vitY < -0.19f) {
            vitY = -0.2f;
        }
    }
        
        
    
    
    
    std::cout << "("<< indiceg << " , " << indice << " , " << indiced << ")\n";
    
//    std::cout<<  topx << "\n";
    bool droitBlock = false;
    if (vitX > 0) {
        if (2 - fmod(posX+botx+1.0f,2) < fabs(vitX)) {
            int ymin = floor((posY-1.0f) / 2.0);
            int ymax = ceil((posY + topy + 1.0f) / 2.0);
//            std::cout << ymin << " , " << ymax << "\n";
            for (int j = indiceg; j <= indiced+1; j++) {
                for (int i = 0; i < (*SharedData::Cases)[j]->size(); i++) {
                    if ((*(*SharedData::Cases)[j])[i]->posY > ymin && (*(*SharedData::Cases)[j])[i]->posY < ymax ) {
                        droitBlock = true;
                        break;
                        //                    std::cout << (*(*SharedData::Cases)[indice + 1])[i]->posY << " , indice = " << indice;
                    }
                }
            }
        }
    }
    
    bool gaucheBlock = false;
    if (vitX < 0) {
        if (fmod(posX+topx-1.0f,2) < fabs(vitX)) {
            int ymin = floor((posY - 1.0f) / 2);
            int ymax = ceil((posY + topy + 1.0f) / 2);
            
            for (int i = 0; i < (*SharedData::Cases)[indiceg -1]->size(); i++) {
                if ((*(*SharedData::Cases)[indiceg -1])[i]->posY > ymin && (*(*SharedData::Cases)[indiceg -1])[i]->posY < ymax ) {
                    gaucheBlock = true;
                    break;
                }
            }
            if (!gaucheBlock) {
                for (int i = 0; i < (*SharedData::Cases)[indiceg]->size(); i++) {
                    if ((*(*SharedData::Cases)[indiceg])[i]->posY > ymin && (*(*SharedData::Cases)[indiceg])[i]->posY < ymax ) {
                        gaucheBlock = true;
                        break;
                    }
                }
            }
        }
    }
    
    
    
    //alors, il faut
    //tester pour les block de xmin a xmax si il sont en dessous ou au dessus pour savoir si on peu continuer de monter et sinon si on doit tomber!
    bool hautBlock = false;
    
    if (vitY > 0) {
        if ( fmod(posY + topy + 1,2) < fabs(vitY)) {
//            int xmin = floor((posX + botx) / 2);
//            int xmax = ceil((posX + topx) / 2);
            int ymax = ceil((posY + topy) / 2);
            
            for (int i = indiceg; i <= indiced; i++) {
                for (int j = 0; j < (*SharedData::Cases)[i]->size(); j++) {
                    if (ymax == (*(*SharedData::Cases)[i])[j]->posY) {
                        hautBlock = true;
                        vitY = 0.0f;
                    }
                }
            }
        }
    }
    
    
    bool basBlock = false;
    
    if (vitY < 0.0f) {
        if ( fmod(posY+ 1.0f , 2) < fabs(vitY)) {
//            int xmin = floor((posX + botx) / 2);
//            int xmax = ceil((posX + topx) / 2);
            int ymin = floor((posY ) / 2);
            
            for (int i = indiceg; i <= indiced; i++) {
                for (int j = 0; j < (*SharedData::Cases)[i]->size(); j++) {
                    if (ymin == (*(*SharedData::Cases)[i])[j]->posY) {
                        basBlock = true;
                        vitY = 0.0f;
                    }
                }
            }
            
        }
    }
    
    if (!droitBlock && vitX > 0) {
        posX += vitX;
    }
    if (!gaucheBlock && vitX < 0) {
        posX += vitX;
    }
    if (!hautBlock && vitY > 0) {
        posY += vitY;
    }
    if (!basBlock && vitY < 0) {
        posY += vitY;
    }
    
}

void Reginaldo::left() {
    setAnim(AnimEnum::R_WALK);
    rot = 90.0f;
    vitX = -0.3f;
    
    direction = false;
    
}
void Reginaldo::leftEnd(){
    setAnim(AnimEnum::R_NOMOVE);
    
    vitX = 0.0f;
}
void Reginaldo::right(){
    setAnim(AnimEnum::R_WALK);
    rot = 270.0f;
    
    vitX = 0.3f;
    
    direction = true;
}
void Reginaldo::rightEnd(){
    setAnim(AnimEnum::R_NOMOVE);
    
    vitX = 0.0f;
}
void Reginaldo::up(){}
void Reginaldo::upEnd(){}
void Reginaldo::down(){
    setAnim(AnimEnum::R_BEND);
}
void Reginaldo::downEnd(){
    setAnim(AnimEnum::R_BENDEND);
}
void Reginaldo::action1(){
    vitY = 0.51f;
}
void Reginaldo::action1End(){}
void Reginaldo::action2(){}
void Reginaldo::action2End(){}