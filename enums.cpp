//
//  enums.cpp
//  SuperReginaldo
//
//  Created by memo on 04/03/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "enums.h"

anim_t AnimEnum::R_WALK = {0, REG_WALK, REG_NOTHING}; // marcher
anim_t AnimEnum::R_NOMOVE = {1, REG_NOMOVE, REG_NOTHING}; // ne pas bouger
anim_t AnimEnum::R_JUMP = {2, REG_JUMP, REG_JUMPSTATIC}; // saut
anim_t AnimEnum::R_DOUBLEJUMP = {3, REG_DOUBLEJUMP, REG_DOUBLEJUMPSTATIC}; // double saut
anim_t AnimEnum::R_JUMPL = {4, REG_JUMPL, REG_JUMPLSTATIC}; // saut en longueur
anim_t AnimEnum::R_SLIDE = {5, REG_SLIDE, REG_SLIDESTATIC}; // slide sur un mur
anim_t AnimEnum::R_WALLJUMP = {6, REG_WALLJUMP, REG_JUMPSTATIC}; // saut apres le slide sur le mur
anim_t AnimEnum::R_JUMPEND = {7, REG_JUMPEND, REG_NOMOVE}; // fin du saut
anim_t AnimEnum::R_DOUBLEJUMPEND = {8, REG_DOUBLEJUMPEND, REG_NOMOVE}; // fin du double saut
anim_t AnimEnum::R_JUMPLEND = {9, REG_JUMPLEND, REG_NOMOVE}; // fin du saut en longueur
anim_t AnimEnum::R_DOUBLEBACKFLIP = {10, REG_DOUBLEBACKFLIP, REG_JUMPSTATIC}; // double saut perilleux arriere
anim_t AnimEnum::R_BEND = {11, REG_BEND, REG_BENDSTATIC}; // se baisser
anim_t AnimEnum::R_BENDEND = {12, REG_BENDUP, REG_NOMOVE}; // se relever
anim_t AnimEnum::R_KICK = {13, REG_KICK, REG_NOMOVE}; // coup de pied

