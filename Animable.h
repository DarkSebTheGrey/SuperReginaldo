#ifndef __ANIMABLE_H__
#define __ANIMABLE_H__

#include <string>
#include <memory>

#include "Affichable.h"
#include "Md2Entity.h"

struct anim_t
{
    int id;
    int start;
    int end;
};

class Animable : public Affichable
{
public:
    Md2Box_t* boxLeft();
    Md2Box_t* boxRight();


    Animable(Md2Entity *entity, anim_t defaultAnim, int defaultSkin);
    ~Animable();
    void affiche();
    void anim(); // current frame update
    void setAnim(anim_t anim); // change immediatly current anim
    void setTexture(int id); // change immediatly current texture
    int getAnim()
    {
        return _anim;
    }
    int getSkin()
    {
        return _skin;
    }
    Md2Entity* model()
    {
        return _entity;
    }
private:
//    int _start;
    int _anim; // current anim
    int _skin; // current texture
    Md2Entity *_entity;
};

#endif
