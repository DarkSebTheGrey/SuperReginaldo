/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Definition of an OpenGL texture class
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "ImagePCX.h"

class Texture
{
public:
    Texture(const std::string &filename);
//    Texture(const ImagePCX *img);
    ~Texture();
    void bind() const;
    bool fail() const
    {
        return _fail;
    }
    bool stdCoordSystem() const
    {
        return _standardCoordSystem;
    }
    int id() const
    {
        return _id;
    }
private:
    Texture() { }
    Texture(const Texture &);
    Texture &operator=(const Texture &);
    int _id;
    GLuint _handle;
    bool _standardCoordSystem;
    bool _fail;
};

#endif
