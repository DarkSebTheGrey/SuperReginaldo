//
//  SharedData.h
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __BaseEngine__SharedData__
#define __BaseEngine__SharedData__

#include "GLUT.h"


#include <iostream>
#include <vector>
#include "Stopwatch.h"
#include "Case.h"
#include "enums.h"
#include "Perso.h"

class SharedData {
public:

    //graphicData
    static GLdouble eyeX;
    static GLdouble eyeY;
    static GLdouble eyeZ;
    static GLdouble centerX;
    static GLdouble centerY;
    static GLdouble centerZ;
    static GLdouble upX;
    static GLdouble upY;
    static GLdouble upZ;
    static GLuint buffers[3];


    static GLfloat *VertexArray;
    static GLsizei VertexArraySize;
    static int VertexArrayState;

    static GLfloat *TextArray;
    static GLsizei TextArraySize;
    static int TextArrayState;

    static GLuint *IndiceArray;
    static GLsizei IndiceArraySize;
    static int IndiceArrayState;

    static bool fpsAffichage;

    //Animable Data
    static Md2Entity *REGINALDO_E ;
    static Md2Entity *GOOMBA_E ;
    static Md2Entity *PIRANHA_E;

    //gameData

    static int etat;

    static int nbCases;

    static std::vector<std::vector<Case *> * > * Cases;

    static Stopwatch gameControlSwatch;

    //vecteur des perso avec en premiere position le P1 toujours present (RPZ)

    static std::vector<Perso *> persos;

    static int textCoord[6][2];


};
#endif /* defined(__BaseEngine__SharedData__) */
