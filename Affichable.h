#ifndef __AFFICHABLE_H__
#define __AFFICHABLE_H__

class Affichable
{
public:
    Affichable();
    virtual ~Affichable();
    virtual void affiche() =0; // draw current frame
};

#endif
