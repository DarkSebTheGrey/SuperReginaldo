//
//  GraphicEngine.h
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __BaseEngine__GraphicEngine__
#define __BaseEngine__GraphicEngine__

#include <GL/glew.h>
#include <iostream>
#include "Engine.h"
#include "GLUT.h"
#include "GraphicCallback.h"
#include "ControlCallback.h"
#include "GameCallback.h"
#include "TextureBuilder.h"

#include "TextureManager.h"

static void initGame()
{
    // UBER IMPORTANT: INIT OF TEXTURES MATRIX SIZE, ONCE FOR ALL GAME ENTITIES
    TextureManager *texMgr = TextureManager::getInstance();
    std::vector<int> v2;
    v2.push_back(SharedData::REGINALDO_E->nbTextures());
    v2.push_back(SharedData::GOOMBA_E->nbTextures());
    v2.push_back(SharedData::PIRANHA_E->nbTextures());
    texMgr->setInstances(v2);

    // INIT ONCE GAME ENTITIES
    SharedData::REGINALDO_E->init(270,90);
    SharedData::GOOMBA_E->init(240,240-180);
    SharedData::PIRANHA_E->init(240,240-180);
}


class GraphicEngine:public Engine {

    void loadMap();
public:
    GraphicEngine(int argc,char * argv[]){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(640,480);
        glutCreateWindow("Super Reginaldo");
        glewInit();
        //glutFullScreen();

        glClearColor(0.0,0.0,0.0,0.0);

        //enable the base state
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);

        //suppression du repetage des touche
        glutIgnoreKeyRepeat( true );



        glutDisplayFunc(display);
        glutReshapeFunc(ReshapeCallback);
        glutKeyboardFunc(KeyboardCallback);
        glutKeyboardUpFunc(KeyboardReleaseCallback);
        glutSpecialFunc(specialCallback);
        glutMouseFunc(MouseCallback);
        glutMotionFunc(MotionCallback);
        glutPassiveMotionFunc(PassiveMotionCallback);
        glutIdleFunc(IdleCallback);

        //chargement des texture des maps
        TextureBuilder::brickText = TextureBuilder::loadBMP_custom("atlas.bmp");

        glGenBuffers(3, SharedData::buffers);

        //futur buffer des vertex
        glBindBuffer(GL_ARRAY_BUFFER, SharedData::buffers[0]);
        glBufferData(GL_ARRAY_BUFFER,0, NULL, GL_DYNAMIC_DRAW);

        //futur buffer des texture
        glBindBuffer(GL_ARRAY_BUFFER, SharedData::buffers[2]);
        glBufferData(GL_ARRAY_BUFFER,0, NULL, GL_DYNAMIC_DRAW);

        // Buffer d'indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SharedData::buffers[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,0, NULL, GL_DYNAMIC_DRAW);



        initGame();

    }

    void start(){
        glutMainLoop();
    }

    void processEvent();

};

#endif /* defined(__BaseEngine__GraphicEngine__) */
