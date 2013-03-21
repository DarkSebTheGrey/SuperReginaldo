#include "Animable.h"

Animable::Animable(Md2Entity *entity, anim_t defaultAnim, int defaultSkin)
    : _skin(defaultSkin)
{
    _entity = new Md2Entity(*entity);
    setAnim(defaultAnim);
    _entity->setSkin(_skin);
}

Animable::~Animable()
{
    delete _entity;
}

void Animable::affiche()
{
    _entity->affiche();
}

void Animable::anim()
{
    _entity->anim();
}


void Animable::setAnim(anim_t anim)
{
    _anim = anim.id;
//    _start = anim.start;
    _entity->setAnim(anim.start, anim.end);
}

void Animable::setTexture(int id)
{
    _skin = id;
    _entity->setSkin(id);
}

Md2Box_t* Animable::boxLeft()
{
    return _entity->model()->boxesL(_entity->box());
}

Md2Box_t* Animable::boxRight()
{
    return _entity->model()->boxesR(_entity->box());
}
