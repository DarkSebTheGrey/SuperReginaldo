//
//  GameEngine.cpp
//  SuperReginaldo
//
//  Created by memo on 27/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "GameEngine.h"

void GameEngine::processEvent(){
    while (hasNextEvent()) {
        Event * e = getNextEvent();
        //faire un case...
        switch (e->getType()) {
            case LOADLVL:
                loadLvl();
                break;
            case SAVELVL:
                saveLvl();
                break;
            case REFRESHCASE:
                makeLvlArrays();
                Engine::sendEvent(new Event(LOADMAP));
                Engine::seekEvent();
                break;
            case P1RIGHT:
                SharedData::persos[0]->right();
                break;
            case P1LEFT:
                SharedData::persos[0]->left();
                break;
            case P1RIGHTEND:
                SharedData::persos[0]->rightEnd();
                break;
            case P1LEFTEND:
                SharedData::persos[0]->leftEnd();
                break;
            case P1UP:
                SharedData::persos[0]->up();
                break;
            case P1UPEND:
                SharedData::persos[0]->upEnd();
                break;
            case P1DOWN:
                SharedData::persos[0]->down();
                break;
            case P1DOWNEND:
                SharedData::persos[0]->downEnd();
                break;
            case P1ACTION1:
                SharedData::persos[0]->action1();
                break;
            case P1ACTION1END:
                SharedData::persos[0]->action1End();
                break;
            case P1ACTION2:
                SharedData::persos[0]->action2();
                break;
            case P1ACTION2END:
                SharedData::persos[0]->action2End();
                break;
//            case <#constant#>:
//                <#statements#>
//                break;
            default:
                break;
        }
    }
}

void GameEngine::loadLvl(){
    f = new std::ifstream("k.lvl");
    if(*f){
        int nbOccurence;
        int tailleVector;

        (*f) >> nbOccurence;
        (*f) >> tailleVector;

        //std::cout << nbOccurence << " - " << tailleVector << "\n";

        if (SharedData::Cases != 0) {
            for (int i=0; i < SharedData::Cases->size(); i++) {
                for (int j = 0; j < (*SharedData::Cases)[i]->size(); j++) {
                    delete (*(*SharedData::Cases)[i])[j];
                }
            }
            delete SharedData::Cases;
        }

        SharedData::Cases = new std::vector<std::vector<Case *> * >(tailleVector);
        for (int i=0; i <SharedData::Cases->size() ; i++) {
            (*SharedData::Cases)[i] = new std::vector<Case *>();
        }
        SharedData::nbCases = 0;

        int type,indice,y;

        for (int i= 0; i < nbOccurence; i++) {
            (*f) >> type;
            (*f) >> indice;
            (*f) >> y;
            (*SharedData::Cases)[indice]->push_back(new Case(indice,y,type));
            SharedData::nbCases ++;
        }

        makeLvlArrays();
        Engine::sendEvent(new Event(LOADMAP));
        Engine::seekEvent();
    }else{
        std::cout << "probleme ouverture du fichier de lvl\n";
    }
    delete f;
}

void GameEngine::saveLvl(){
    of = new std::ofstream("k.lvl");
    if (*of) {

        (*of) << SharedData::nbCases << " ";

        (*of) << SharedData::Cases->size() << " ";

        for (int i=0; i < SharedData::Cases->size(); i++) {
            for (int j = 0; j < (*SharedData::Cases)[i]->size(); j++) {
                (*of) << (*(*SharedData::Cases)[i])[j]->type << " ";
                (*of) << (*(*SharedData::Cases)[i])[j]->posX << " ";
                (*of) << (*(*SharedData::Cases)[i])[j]->posY << " ";
            }
        }

    }else{
        std::cout << "probleme ouverture du fichier de lvl\n";
    }
    delete of;
}




void GameEngine::makeLvlArrays(){

    SharedData::VertexArraySize = SharedData::nbCases * 48;
    SharedData::VertexArray = new GLfloat[SharedData::VertexArraySize];
    SharedData::VertexArrayState = 0;

    SharedData::TextArraySize = SharedData::nbCases * 32;
    SharedData::TextArray = new GLfloat[SharedData::TextArraySize];
    SharedData::TextArrayState = 0;

    SharedData::IndiceArraySize = SharedData::nbCases * 36;
    SharedData::IndiceArray = new GLuint[SharedData::IndiceArraySize];
    SharedData::IndiceArrayState = 0;

    for (int i=0; i < SharedData::Cases->size(); i++) {
        for (int j = 0; j < (*SharedData::Cases)[i]->size(); j++) {
            addCases((*(*SharedData::Cases)[i])[j]);
        }
    }
}

void GameEngine::addCases(Case *c){
    //v1

    float x,y,z;
    x = c->posX * 2.0;
    y = c->posY * 2.0;
    z = 0.0;
    int i = SharedData::textCoord[c->type][0];
    int j = SharedData::textCoord[c->type][1];

    float textXD = i  *  0.0625 + 1.0/256.0;
    float textXF = i  *  0.0625 + 0.0625 + 1.0/256.;
    float textYD = j  *  0.0625 ;
    float textYF = j  *  0.0625 + 0.0625;

    //un
    //v1
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //deux
    //v2
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //trois
    //v3
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //quattre
    //v4
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //cinq
    //v6
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //six
    //v7
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //sept
    //v5
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //huit
    //v8
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //neuf
    //v5
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //dix
    //v6
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //onze
    //v2
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //douze
    //v1
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //treize
    //v8
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //quatorze
    //v7
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z + tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYF;

    //quinze
    //v3
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x + tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXF;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //seize
    //v4
    SharedData::VertexArray[SharedData::VertexArrayState++] = (x - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (y - tailleBlockSurDeux);
    SharedData::VertexArray[SharedData::VertexArrayState++] = (z - tailleBlockSurDeux);

    SharedData::TextArray[SharedData::TextArrayState++] = textXD;
    SharedData::TextArray[SharedData::TextArrayState++] = textYD;

    //formation des triangles
    GLuint seize = (SharedData::VertexArrayState / 3) -1;
    GLuint quinze = seize -1;
    GLuint quatorze = quinze -1;
    GLuint treize = quatorze - 1;
    GLuint douze =  treize - 1;
    GLuint onze = douze -1;
    GLuint dix = onze -1;
    GLuint neuf = dix -1;
    GLuint huit = neuf -1;
    GLuint sept = huit - 1;
    GLuint six = sept - 1;
    GLuint cinq = six - 1;
    GLuint quattre = cinq - 1;
    GLuint trois = quattre - 1;
    GLuint deux = trois - 1;
    GLuint un = deux - 1;

    //avant
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (un);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (deux);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (trois);

    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (un);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (trois);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (quattre);

    //droit
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (deux);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (cinq);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (six);

    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (deux);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (six);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (trois);

    //gauche
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (un);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (sept);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (huit);

    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (un);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (huit);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (quattre);

    //arriere
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (sept);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (cinq);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (six);

    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (sept);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (six);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (huit);

    //dessus
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (neuf);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (dix);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (onze);

    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (neuf);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (onze);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (douze);

    //dessous
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (treize);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (quatorze);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (quinze);

    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (treize);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (quinze);
    SharedData::IndiceArray[SharedData::IndiceArrayState++] = (seize);
    // std::cout << SharedData::IndiceArrayState << "\n";
}









