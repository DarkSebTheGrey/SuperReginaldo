/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Impelementation of MD2 Model Classes
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <math.h>

#include "Md2Model.h"
#include "TextureManager.h"

int Md2Model::_kMd2Ident = 'I' +('D'<<8) +('P'<<16) +('2'<<24);
int Md2Model::_kMd2Version = 8;

Md2Model::Md2Model(const std::string &filename, int id, double left, double right)
: _skins(),
_texCoords(),
_triangles(),
_frames(),
_skinIds(id)
{
    std::ifstream ifs(filename.c_str(), std::ios::binary);
    if(ifs.fail())
    {
        std::cerr << "\nCouldn't open file";
    }
    ifs.read(reinterpret_cast<char *>(&_header), sizeof(Md2Header_t));
    if(_header.ident != _kMd2Ident)
    {
        std::cerr << "\nBad file ident";
    }
    if(_header.version != _kMd2Version)
    {
        std::cerr << "\nBad file version";
    }
    // Memory allocation for model data
    _skins = new Md2Skin_t[_header.num_skins];
    _texCoords = new Md2TexCoord_t[_header.num_st];
    _triangles = new Md2Triangle_t[_header.num_tris];
    _frames = new Md2Frame_t[_header.num_frames];
    _boxesR = new Md2Box_t[_header.num_frames];
    _boxesL = new Md2Box_t[_header.num_frames];

    ifs.seekg(_header.offset_skins, std::ios::beg);
    ifs.read(reinterpret_cast<char *>(_skins), sizeof(Md2Skin_t) * _header.num_skins);
    ifs.seekg(_header.offset_st, std::ios::beg);
    ifs.read(reinterpret_cast<char *>(_texCoords), sizeof(Md2TexCoord_t) * _header.num_st);
    ifs.seekg(_header.offset_tris, std::ios::beg);
    ifs.read(reinterpret_cast<char *>(_triangles), sizeof(Md2Triangle_t) * _header.num_tris);
    ifs.seekg(_header.offset_frames, std::ios::beg);
    for(int i = 0; i < _header.num_frames; ++i)
    {
        // Memory allocation for the vertices of this frame
        _frames[i].verts = new Md2Vertex_t[_header.num_vertices];
        ifs.read(reinterpret_cast<char *>(&_frames[i].scale), sizeof(vec3_t));
        ifs.read(reinterpret_cast<char *>(&_frames[i].translate), sizeof(vec3_t));
        ifs.read(reinterpret_cast<char *>(&_frames[i].name), sizeof(char) * 16);
        ifs.read(reinterpret_cast<char *>(_frames[i].verts), sizeof(Md2Vertex_t) * _header.num_vertices);
    }
    ifs.close();
    setupAnimations();
    setupCollisions(left, right);
    setupMedianCollisions();
}

Md2Model::~Md2Model()
{
    delete [] _skins;
    delete [] _texCoords;
    delete [] _triangles;
    delete [] _frames;
    delete [] _boxesR;
    delete [] _boxesL;
}

bool Md2Model::loadTexture(const std::string &filename, int dir, int id)
{
    TextureManager *texMgr = TextureManager::getInstance();
    Texture *tex = texMgr->load(filename, dir, id);
    if(!tex->fail())
    {
        _skinIds[id] = tex;
    }
    return(!tex->fail());
}

void Md2Model::setupCollisions(double left, double right)
{
    // foreach frame
    for(int f = 0; f < _header.num_frames; ++f)
    {
        double botx = std::numeric_limits<double>::min(); // on cherche le + grand
        double boty = std::numeric_limits<double>::max(); // on cherche le + petit
        double topx = std::numeric_limits<double>::max(); // on cherche le + petit
        double topy = std::numeric_limits<double>::min(); // on cherche le + grand
        // for each triangle
        for(int i = 0; i < _header.num_tris; ++i)
        {
            // for each vertex of this triangle
            for(int j = 0; j < 3; ++j)
            {
                Md2Frame_t *pFrame = &_frames[f];
                Md2Vertex_t *pVert = &pFrame->verts[_triangles[i].vertex[j]];
                // Uncompress vertex position and scale it
                vec3_t v;
                double rot((360-left)*3.141597/180.0);
                v[0] =(pFrame->scale[0] * pVert->v[0] + pFrame->translate[0])*cos(rot)+(pFrame->scale[2] * pVert->v[2] + pFrame->translate[2])*(-sin(rot));
                v[1] =(pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]);
                v[2] =sin(rot)*(pFrame->scale[2] * pVert->v[2] + pFrame->translate[2])+(pFrame->scale[0] * pVert->v[0] + pFrame->translate[0])*cos(rot);
                if(v[0] <= topx)
                {
                    topx = v[0];
                }
                else if(v[0] >= botx)
                {
                    botx = v[0];
                }
                if(v[1] >= topy)
                {
                    topy = v[1];
                }
                else if(v[1] <= boty)
                {
                    boty = v[1];
                }
            }
        }
        _boxesL[f].topleftx = topx;
        _boxesL[f].toplefty = topy;
        _boxesL[f].bottomrightx = botx;
        _boxesL[f].bottomrighty = boty;
        botx = std::numeric_limits<double>::min(); // on cherche le + grand
        boty = std::numeric_limits<double>::max(); // on cherche le + petit
        topx = std::numeric_limits<double>::max(); // on cherche le + petit
        topy = std::numeric_limits<double>::min(); // on cherche le + grand
        for(int i = 0; i < _header.num_tris; ++i)
        {
            // for each vertex of this triangle
            for(int j = 0; j < 3; ++j)
            {
                Md2Frame_t *pFrame = &_frames[f];
                Md2Vertex_t *pVert = &pFrame->verts[_triangles[i].vertex[j]];
                // Uncompress vertex position and scale it
                vec3_t v;
                double rot((360-right)*3.141597/180.0);
                v[0] =(pFrame->scale[0] * pVert->v[0] + pFrame->translate[0])*cos(rot)+(pFrame->scale[2] * pVert->v[2] + pFrame->translate[2])*(-sin(rot));
                v[1] =(pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]);
                v[2] =sin(rot)*(pFrame->scale[2] * pVert->v[2] + pFrame->translate[2])+(pFrame->scale[0] * pVert->v[0] + pFrame->translate[0])*cos(rot);
                if(v[0] <= topx)
                {
                    topx = v[0];
                }
                else if(v[0] >= botx)
                {
                    botx = v[0];
                }
                if(v[1] >= topy)
                {
                    topy = v[1];
                }
                else if(v[1] <= boty)
                {
                    boty = v[1];
                }
            }
        }
        _boxesR[f].topleftx = topx;
        _boxesR[f].toplefty = topy;
        _boxesR[f].bottomrightx = botx;
        _boxesR[f].bottomrighty = boty;
    }
}

void Md2Model::setupAnimations()
{
    std::string currentAnim;
    Md2Anim_t animInfo = {0, 0};
    for(int i = 0; i < _header.num_frames; ++i)
    {
        std::string frameName = _frames[i].name;
        std::string frameAnim;

        // Extract animation name from frame name
        std::string::size_type len = frameName.find_first_of("0123456789");
        if((len == frameName.length() - 3) && (frameName[len] != '0'))
        {
            len++;
        }
        frameAnim.assign(frameName, 0, len);
        if(currentAnim != frameAnim)
        {
            if(i > 0)
            {
                // Previous animation is finished, insert it and start new animation.
                _anims.push_back(animInfo);
            }
            // Initialize new anim info
            animInfo.start = i;
            animInfo.end = i;
            currentAnim = frameAnim;
        }
        else
        {
            animInfo.end = i;
        }
    }
    // Insert last animation
    _anims.push_back(animInfo);
}

void Md2Model::setupMedianCollisions()
{
    int frame(0), frametmp(0);
    for(unsigned int i = 0; i < _anims.size(); i++)
    {
        double topx(0),topy(0),botx(0),boty(0);
        double topxl(0),topyl(0),botxl(0),botyl(0);
        for(int j = _anims[i].start; j <= _anims[i].end; j++)
        {
            frametmp++;
            topx+=_boxesR[frametmp].topleftx;
            topxl+=_boxesL[frametmp].topleftx;
            topy+=_boxesR[frametmp].toplefty;
            topyl+=_boxesL[frametmp].toplefty;
            botx+=_boxesR[frametmp].bottomrightx;
            botxl+=_boxesL[frametmp].bottomrightx;
            boty+=_boxesR[frametmp].bottomrighty;
            botyl+=_boxesL[frametmp].bottomrighty;
        }
        topx = topx/(double)(_anims[i].end-_anims[i].start+1);
        topy = topy/(double)(_anims[i].end-_anims[i].start+1);
        botx = botx/(double)(_anims[i].end-_anims[i].start+1);
        boty = boty/(double)(_anims[i].end-_anims[i].start+1);
        topxl = topxl/(double)(_anims[i].end-_anims[i].start+1);
        topyl = topyl/(double)(_anims[i].end-_anims[i].start+1);
        botxl = botxl/(double)(_anims[i].end-_anims[i].start+1);
        botyl = botyl/(double)(_anims[i].end-_anims[i].start+1);
        for(int j = _anims[i].start; j <= _anims[i].end; j++)
        {
            _boxesR[frame].topleftx = topx;
            _boxesR[frame].toplefty = topy;
            _boxesR[frame].bottomrightx = botx;
            _boxesR[frame].bottomrighty = boty;
            _boxesL[frame].topleftx = topxl;
            _boxesL[frame].toplefty = topyl;
            _boxesL[frame].bottomrightx = botxl;
            _boxesL[frame].bottomrighty = botyl;
            frame++;
        }
    }
}

void Md2Model::renderFrameImmediate(int frame)
{
    int maxFrame = _header.num_frames - 1;
    if((frame < 0) || (frame > maxFrame))
    {
        return;
    }
    glBegin(GL_TRIANGLES);
    // Draw each triangle
    for(int i = 0; i < _header.num_tris; ++i)
    {
        // Draw each vertex of this triangle
        for(int j = 0; j < 3; ++j)
        {
            Md2Frame_t *pFrame = &_frames[frame];
            Md2Vertex_t *pVert = &pFrame->verts[_triangles[i].vertex[j]];
            Md2TexCoord_t *pTexCoords = &_texCoords[_triangles[i].st[j]];
            // Compute final texture coords.
            GLfloat s = static_cast<GLfloat>(pTexCoords->s) / _header.skinwidth;
            GLfloat t = static_cast<GLfloat>(pTexCoords->t) / _header.skinheight;
            glTexCoord2f(s, 1.0f - t);
            // Uncompress vertex position and scale it
            vec3_t v;
            v[0] = (pFrame->scale[0] * pVert->v[0] + pFrame->translate[0]);
            v[1] = (pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]);
            v[2] = (pFrame->scale[2] * pVert->v[2] + pFrame->translate[2]);
            glVertex3fv(v);
        }
    }
    glEnd();
}
