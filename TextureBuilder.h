
#ifndef TEXTUREBUILDER_H
#define TEXTUREBUILDER_H
#include "GLUT.h"
#include <iostream>

class TextureBuilder {

public:
    static GLuint loadBMP_custom(const char * imagepath);

    static int brickText;

};
#endif
