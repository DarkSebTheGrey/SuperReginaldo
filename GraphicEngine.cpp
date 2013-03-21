//
//  GraphicEngine.cpp
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "glew.h"
#include "GraphicEngine.h"

void GraphicEngine::processEvent(){
    while (hasNextEvent()) {
        Event * e = getNextEvent();
        if (e->getType() == LOADMAP) {
            loadMap();
        }
    }
}

void GraphicEngine::loadMap(){

    glBindBuffer(GL_ARRAY_BUFFER, SharedData::buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * SharedData::VertexArraySize, &SharedData::VertexArray[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, SharedData::buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * SharedData::TextArraySize, &SharedData::TextArray[0], GL_DYNAMIC_DRAW);

    // Buffer d'indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SharedData::buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint) *  SharedData::IndiceArraySize,  &SharedData::IndiceArray[0], GL_DYNAMIC_DRAW);

}
