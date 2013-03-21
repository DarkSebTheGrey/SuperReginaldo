//
//  Deplacable.h
//  SuperReginaldo
//
//  Created by memo on 26/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef __SuperReginaldo__Deplacable__
#define __SuperReginaldo__Deplacable__

#include <iostream>
#include "Case.h"

class Deplacable {
    
public:
    virtual void deplace() = 0;
    Case *currentCase;//case sur laquel on marche! (possiblement null (ex: lors d'un saut))
};

#endif /* defined(__SuperReginaldo__Deplacable__) */
