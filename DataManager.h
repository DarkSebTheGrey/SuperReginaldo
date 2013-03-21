/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Definitions of a data manager class which can(un)register generic objects.
// Destroy all registred objects at death.
// The data manager is a singleton.
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __DATAMANAGER_H__
#define __DATAMANAGER_H__

#include <string>
#include <vector>

template <typename T, typename C>
class DataManager
{
protected:
    DataManager();
    virtual ~DataManager();

public:
    T *request(int dir, int id);
    void registerObject(int dir, int id, T *object);
    void purge();
    // Singleton related functions
    static C *getInstance();
    static void kill();
    void setInstance(std::vector<int>& v);
private:
    std::vector<std::vector<T*> > _registryV;
    // The unique instance of this class
    static C *_singleton;
};

#include "DataManager.inl"
#endif
