/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Implementation of MD2 Entitiy Class
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
#include <dirent.h>
#include <sys/types.h>

#include "Md2Entity.h"
#include "Texture.h"
#include "TextureManager.h"
int k(0);
Md2Entity::Md2Entity(const std::string &filename, int nbTextures, int dir)
    : _model(NULL), _name(filename), _framerate(0), _nbTextures(nbTextures), _dir(dir), _currFrame(0), _interp(0.0f), _nextanim(-1), _start(0), _end(0)
{
}

Md2Entity::Md2Entity(const Md2Entity &source)
{
    _model = source._model;
    _currentSkin = source._currentSkin;
    _framerate = source._framerate;
    _currFrame = 0;
    _interp = 0.0f;
    _nextanim = -1;
    _start = 0;
    _end = 0;
}

void Md2Entity::affiche()
{
//    glPushMatrix();
    glFrontFace(GL_CW);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_TEXTURE_2D);
    if(_currentSkin)
    {
        _currentSkin->bind();
    }
    _model->renderFrameImmediate(_currFrame);
//    glDisable(GL_TEXTURE_2D);
//    glDisable(GL_DEPTH_TEST);
//    glPopMatrix();
}

void Md2Entity::anim()
{
    if(_currFrame < _start)
    {
        _currFrame = _start;
    }
    if(_currFrame >= _end && _nextanim != -1)
    {
        setAnim(_nextanim);
    }
    if(_currFrame >= _end)
    {
        _currFrame = _start;
    }
    _currFrame++;
}

void Md2Entity::init( double left, double right)
{
    std::ifstream ifs;
    std::string path, path2;
    dirent *dit;
    DIR *dd;

    path2 = "data/"+_name;
    dd = opendir(path2.c_str());
    if(!dd)
    {
        std::cerr << "\nCouldn't open dir";
    }
    path = "data/" + _name + ".md2";
    ifs.open(path.c_str(), std::ios::binary);
    if(!ifs.fail())
    {
        ifs.close();
        _model = new Md2Model(path, _nbTextures, left, right);
//        std::cerr << "\nnew Md2model: " << path << "\t" << atoi(_name.c_str());
    }
    if(!_model)
    {
        std::cerr << "\nNo model found";
    }
    // Read directory for textures
    while((dit = readdir(dd)) != NULL)
    {
        const std::string file_name(dit->d_name);
        path = "data/" + _name + "/" + file_name;

        std::string::size_type l = file_name.find_last_of('.');
        if(file_name.compare(l, 4, ".pcx") != 0) continue;
//        std::cerr << "\nnload texture: " << path << "\t" << atoi(file_name.c_str());
        _model->loadTexture(path, _dir, atoi(file_name.c_str()));
    }
    closedir(dd);
}

Md2Entity::~Md2Entity()
{
}

void Md2Entity::setSkin(int id)
{
    if(_model->skins()[id] != NULL)
    {
        _currentSkin = _model->skins()[id];
    }
    else
    {
        std::cerr << "\nNO TEXTURE SET";
        _currentSkin = NULL;
    }
}

void Md2Entity::setAnim(int id, int nextid)
{
    _start = (&_model->anims()[id])->start;
    _currFrame = _start; // DARKSEB 2 - 1 FREEZE BUG
    _end = (&_model->anims()[id])->end;
    _nextanim = nextid;
    _box = (nextid == -1)?_start:(&_model->anims()[nextid])->start;
}

void Md2Entity::setnextAnim(int id)
{
    _nextanim = id;
}
