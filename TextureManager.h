/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Definitions of a texture manager class which can
// (un)register Texture2D objects.
// It's a singleton
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include "DataManager.h"
#include "Texture.h"

class TextureManager : public DataManager<Texture, TextureManager>
{
    friend class DataManager<Texture, TextureManager>;
public:
    // Load and register a texture.  If the texture has already been
    // loaded previously, return it instead of loading it
    Texture *load(const std::string &filename, int dir, int id)
    {
        Texture *tex = request(dir, id);
        if(tex == NULL)
        {
            tex = new Texture(filename);
            if(tex->fail())
            {
                delete tex;
                tex = NULL;
            }
            else
            {
                registerObject(dir, id, tex);
            }
        }
        return tex;
    }
    void setInstances(std::vector<int>& v)
    {
        setInstance(v);
    }
};

#endif
