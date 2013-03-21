//
//  SharedData.cpp
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "SharedData.h"

GLuint SharedData::buffers[3];

GLdouble SharedData::eyeX = 12.0;
GLdouble SharedData::eyeY = 5.0;
GLdouble SharedData::eyeZ = 25.0;
GLdouble SharedData::centerX = 12.0;
GLdouble SharedData::centerY = 5.0;
GLdouble SharedData::centerZ = 0.0;
GLdouble SharedData::upX = 0.0;
GLdouble SharedData::upY = 1.0;
GLdouble SharedData::upZ = 0.0;

bool SharedData::fpsAffichage = false;

GLfloat * SharedData::VertexArray;
GLsizei SharedData::VertexArraySize = 0;
int SharedData::VertexArrayState = 0;

GLfloat * SharedData::TextArray;
GLsizei SharedData::TextArraySize = 0;
int SharedData::TextArrayState = 0;

GLuint  * SharedData::IndiceArray;
GLsizei SharedData::IndiceArraySize = 0;
int SharedData::IndiceArrayState = 0;

//Animable Data

Md2Entity *SharedData::REGINALDO_E = new Md2Entity("player", 2, 0);
Md2Entity *SharedData::GOOMBA_E = new Md2Entity("goomba", 1, 1);
Md2Entity *SharedData::PIRANHA_E = new Md2Entity("piranha", 1, 2);


//Game data
int SharedData::etat = 10;

int SharedData::nbCases = 0;

std::vector<std::vector<Case *> * > * SharedData::Cases = 0;

Stopwatch SharedData::gameControlSwatch;

std::vector<Perso *> SharedData::persos;

int SharedData::textCoord[6][2] = {1,15,2,15,3,15,8,15,1,14,10,14};



