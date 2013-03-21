/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Definitions of ImagePCX loader class for PCX Image format
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ImagePCXPCX_H__
#define __ImagePCXPCX_H__

#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

class ImagePCX
{
public:
    ImagePCX(const std::string &filename);
    ~ImagePCX();
    GLsizei width() const
    {
        return _width;
    }
    GLsizei height() const
    {
        return _height;
    }
    GLint numMipmaps() const
    {
        return _numMipmaps;
    }
    GLenum format() const
    {
        return _format;
    }
    GLint components() const
    {
        return _components;
    }
    const GLubyte *pixels() const
    {
        return _pixels;
    }
    const std::string &name() const
    {
        return _name;
    }
    bool stdCoordSystem() const
    {
        return _standardCoordSystem;
    }
    static ImagePCX *createImagePCX(const std::string &filename)
    {
        return new ImagePCX(filename);
    }
private:
    ImagePCX(const ImagePCX &img);
    GLsizei _width;
    GLsizei _height;
    GLint _numMipmaps;
    // OpenGL texture format and internal format(components)
    GLenum _format;
    GLint _components;
    // ImagePCX data
    GLubyte *_pixels;
    std::string _name;
    bool _standardCoordSystem;
    // pcx header
    struct PCX_Header
    {
        GLubyte manufacturer;
        GLubyte version;
        GLubyte encoding;
        GLubyte bitsPerPixel;

        GLushort xmin, ymin;
        GLushort xmax, ymax;
        GLushort horzRes, vertRes;

        GLubyte palette[48];
        GLubyte reserved;
        GLubyte numColorPlanes;

        GLushort bytesPerScanLine;
        GLushort paletteType;
        GLushort horzSize, vertSize;

        GLubyte padding[54];
    };
    const PCX_Header *_header;
    // buffer
    std::string _filename;
    GLubyte *_data;
    size_t _length;
};

#endif
