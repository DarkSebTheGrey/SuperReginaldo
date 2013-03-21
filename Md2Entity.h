/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Definition of MD2 Entity Class
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MD2PLAYER_H__
#define __MD2PLAYER_H__

#include <vector>
#include <string>

#include "Md2Model.h"

class Md2Entity
{
public:
    Md2Entity(const std::string &dirname, int nbTextures, int dir);
    Md2Entity(const Md2Entity &source);
    ~Md2Entity();
    void kill()
    {
        delete _model;
    }
    void init( double left, double right);
    void setSkin(int id);
    void affiche();
    void anim();
    void setAnim(int id, int nextid = -1);
    void setnextAnim(int id);
    const std::string &name() const
    {
        return _name;
    }
    int nbTextures()
    {
        return _nbTextures;
    }
    Md2Model *model()
    {
        return _model;
    }
    int framerate()
    {
        return _framerate;
    }
    void setFrameRate(int x)
    {
        _framerate = x;
    }
    int currFrame()
    {
        return _currFrame;
    }
    void setCurrFrame(int x)
    {
        _currFrame = x;
    }
    const Texture* currentSkin() const
    {
        return _currentSkin;
    }
    int nextAnim()
    {
        return _nextanim;
    }
    int start()
    {
        return _start;
    }
    int end()
    {
        return _end;
    }
    float interp()
    {
        return _interp;
    }
    void setInterp(float x)
    {
        _interp = x;
    }
    int box(){
        return _box;
    }
private:
    Md2Model* _model;
    std::string _name;
    Texture* _currentSkin;
    int _framerate;
    int _nbTextures;
    int _dir;

    int _currFrame;
    float _interp;
    int _nextanim;
    int _start;
    int _end;
    int _box;
};

#endif
