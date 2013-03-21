/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Definition of MD2 Model Classes
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MD2MODEL_H__
#define __MD2MODEL_H__

#include <vector>
#include <string>
#include <vector>

#include "Texture.h"

// OpenGL vector types
typedef GLfloat vec2_t[2];
typedef GLfloat vec3_t[3];

// Md2 header
struct Md2Header_t
{
    int ident;          // Magic number, "IDP2"
    int version;        // Md2 format version, should be 8
    
    int skinwidth;      // Texture width
    int skinheight;     // Texture height
    
    int framesize;      // Size of a frame, in bytes
    
    int num_skins;      // Number of skins
    int num_vertices;   // Number of vertices per frame
    int num_st;         // Number of texture coords
    int num_tris;       // Number of triangles
    int num_glcmds;     // Number of OpenGL commands
    int num_frames;     // Number of frames
    
    int offset_skins;   // offset to skin data
    int offset_st;      // offset to texture coords
    int offset_tris;    // offset to triangle data
    int offset_frames;  // offset to frame data
    int offset_end;     // offset to the end of the file
};

// Skin data
struct Md2Skin_t
{
    char name[64];  // Texture's filename
};

// Texture coords.
struct Md2TexCoord_t
{
    short s;
    short t;
};

// Triangle data
struct Md2Triangle_t
{
    unsigned short vertex[3];  // Triangle's vertex indices
    unsigned short st[3];      // Texture coords. indices
};

// Vertex data
struct Md2Vertex_t
{
    unsigned char v[3];         // Compressed vertex position
    unsigned char normalIndex;  // Normal vector index
};


// Vertex data
struct Md2Box_t
{
    double topleftx;
    double toplefty;
    double bottomrightx;
    double bottomrighty;
};


// Frame data
struct Md2Frame_t
{
    ~Md2Frame_t()
    {
        delete [] verts;
    }
    vec3_t scale;        // Scale factors
    vec3_t translate;    // Translation vector
    char name[16];       // Frame name
    Md2Vertex_t *verts;  // Frames's vertex list
};

// Animation infos
struct Md2Anim_t
{
    int start;  // first frame index
    int end;    // last frame index
};

class Md2Model
{
public:
    Md2Model(const std::string &filename, int id, double left, double right);
    ~Md2Model();
    typedef std::vector<Texture*> SkinMap;
    typedef std::vector<Md2Anim_t> AnimMap;
    bool loadTexture(const std::string &filename, int dir, int id);
    void setTexture(int id);
    void renderFrameImmediate(int frame);
    const SkinMap &skins() const
    {
        return _skinIds;
    }
    const AnimMap &anims() const
    {
        return _anims;
    }
    Texture* skin(int id)
    {
        return _skinIds[id];
    }
    Md2Box_t* boxesL(int id) const
    {
        return &(_boxesL[id]);
    }
    Md2Box_t* boxesR(int id) const
    {
        return &(_boxesR[id]);
    }
private:
    void setupAnimations();
    void setupCollisions( double left, double right);
    void setupMedianCollisions();
    static int _kMd2Ident;
    static int _kMd2Version;
    Md2Header_t _header;
    Md2Skin_t *_skins;
    Md2TexCoord_t *_texCoords;
    Md2Triangle_t *_triangles;
    Md2Frame_t *_frames;
    Md2Box_t *_boxesL;
    Md2Box_t *_boxesR;
    SkinMap _skinIds;
    AnimMap _anims;
};

#endif
