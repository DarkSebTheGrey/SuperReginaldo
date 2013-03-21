/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Implementation of a data manager class
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#include "DataManager.h"

template <typename T, typename C> C *DataManager<T, C>::_singleton = NULL;

template <typename T, typename C> inline DataManager<T, C>::DataManager()
{
}

template <typename T, typename C> inline DataManager<T, C>::~DataManager()
{
    purge();
}

// Retrieve an object from the registry
template <typename T, typename C> inline T* DataManager<T, C>::request(int dir, int id)
{
    return _registryV[dir][id];
}

// Register an object
template <typename T, typename C> inline void DataManager<T, C>::registerObject(int dir, int id, T *object)
{
    _registryV[dir][id] = object;
}

// Destroy all registred objects and clear the registry
template <typename T, typename C> inline void DataManager<T, C>::purge()
{
    for(unsigned int dir = 0; dir < _registryV.size(); dir++)
    {
        for(unsigned int id = 0; id < _registryV[dir].size(); id++)
        {
            if(_registryV[dir][id] != NULL)
            {
                delete _registryV[dir][id];
                _registryV[dir][id] = NULL;
            }
        }
    }
}

// Return a pointer of the unique instance of this class
// SET INSTANCE MUST BE CALLED FIRST
template <typename T, typename C> inline C * DataManager<T, C>::getInstance()
{
    if(_singleton == NULL)
    {
        _singleton = new C;
    }
    return _singleton;
}

// MUST BE CALLED ONCE
template <typename T, typename C> inline void DataManager<T, C>::setInstance(std::vector<int>& v)
{
    for(unsigned int i = 0; i < v.size(); i++)
    {
        std::vector<T*> temp(v[i]);
        _registryV.push_back(temp);
    }
}

// Delete the unique instance of this class
template <typename T, typename C> inline void DataManager<T, C>::kill()
{
    delete _singleton;
    _singleton = NULL;
}
