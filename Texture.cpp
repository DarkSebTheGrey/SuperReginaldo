/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Implementation of an OpenGL texture class
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////
#include "GLUT.h"

#include <iostream>

#include "Texture.h"
#include "ImagePCX.h"

Texture::~Texture()
{
    if(glIsTexture(_handle))
        glDeleteTextures(1, &_handle);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, _handle);
}

Texture::Texture(const std::string &filename)
{
    ImagePCX *img = NULL;
    img = ImagePCX::createImagePCX(filename);
    if (img != NULL)
    {
        if(!img->pixels())
        {
            std::cerr << "\nInvalid image data";
        }
        _id = atoi(img->name().c_str());
        _standardCoordSystem = img->stdCoordSystem();

        glGenTextures(1, &_handle);
        glBindTexture(GL_TEXTURE_2D, _handle);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        // Build the texture and generate mipmaps
        // No hardware mipmap generation support, fall back to the
        // good old gluBuild2DMipmaps function
        gluBuild2DMipmaps(GL_TEXTURE_2D, img->components(),
                          img->width(), img->height(), img->format(),
                          GL_UNSIGNED_BYTE, img->pixels());

        GLenum err = glGetError();
        if(GL_NO_ERROR == err)
        {
            _fail = false;
        }
        else
        {
            std::cerr << "\nOpenGL Error: " << gluErrorString(err) << " [Texture::create()]";
        }
        delete img;
    }
    else
    {
        std::cerr << "\nError: Couldn't create texture 2D from " << filename;
    }
}
