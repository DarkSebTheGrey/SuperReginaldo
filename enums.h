#ifndef __ENUMS_H__
#define __ENUMS_H__

#include <vector>
#include <string>
#include "Animable.h"

class AnimEnum {

public:
    enum REGmove
    {
        REG_NOTHING = -1,
        REG_WALK = 0,
        REG_SLIDE = 1,
        REG_SLIDESTATIC = 2,
        REG_NOMOVE = 3,
        REG_JUMPL = 4,
        REG_JUMPLSTATIC = 5,
        REG_JUMPLEND = 6,
        REG_WALLJUMP = 7,
        REG_JUMP = 9,
        REG_JUMPSTATIC = 10,
        REG_JUMPEND = 11,
        REG_DOUBLEJUMP = 12,
        REG_DOUBLEJUMPSTATIC = 13,
        REG_DOUBLEJUMPEND = 14,
        REG_DOUBLEBACKFLIP = 15,
        REG_BEND = 16,
        REG_BENDSTATIC = 17,
        REG_BENDUP = 18,
        REG_KICK = 19
    };

//    enum GOMmove
//    {
//        GOM_NOTHING = -1,
//        GOM_WALK = 0,
//    };
//    enum FIRmove
//    {
//        FIR_NOTHING = -1,
//        FIR_ANIM = 0,
//    };
//
//    enum PIRmove
//    {
//        PIR_NOTHING = -1,
//        PIR_ANIM = 0,
//        PIR_ANIMSTATIC = 1,
//    };

    static anim_t R_WALK ; // marcher
    static anim_t R_NOMOVE ; // ne pas bouger
    static anim_t R_JUMP ; // saut
    static anim_t R_DOUBLEJUMP ; // double saut
    static anim_t R_JUMPL  ; // saut en longueur
    static anim_t R_SLIDE  ; // slide sur un mur
    static anim_t R_WALLJUMP ; // saut apres le slide sur le mur
    static anim_t R_JUMPEND ; // fin du saut
    static anim_t R_DOUBLEJUMPEND  ; // fin du double saut
    static anim_t R_JUMPLEND ; // fin du saut en longueur
    static anim_t R_DOUBLEBACKFLIP ; // double saut perilleux arriere
    static anim_t R_BEND ; // se baisser
    static anim_t R_BENDEND ; // se relever
    static anim_t R_KICK ; // coup de pied


//    anim_t G_WALK = {0, GOMmove::GOM_WALK, GOMmove::GOM_NOTHING}; // marcher
//    anim_t P_ANIM = {0, PIRmove::PIR_ANIM, PIRmove::PIR_ANIMSTATIC}; // go
//    anim_t F_ANIM = {0, FIRmove::FIR_ANIM, FIRmove::FIR_NOTHING}; // go
//
//    enum hashRegMove // to compare with
//    {
//        HR_WALK = 0,
//        HR_NOMOVE = 1,
//        HR_JUMP = 2,
//        HR_DOUBLEJUMP = 3,
//        HR_JUMPL = 4,
//        HR_SLIDE = 5,
//        HR_WALLJUMP = 6,
//        HR_JUMPEND = 7,
//        HR_DOUBLEJUMPEND = 8,
//        HR_JUMPLEND = 9,
//        HR_DOUBLEBACKFLIP = 10,
//        HR_BEND = 11,
//        HR_BENDEND = 12,
//        HR_KICK = 13,
//    };

};


//std::vector<anim_t> anims ;
//{
//    R_WALK,
//    R_NOMOVE,
//    R_JUMP,
//    R_JUMPEND,
//    R_DOUBLEJUMP,
//    R_DOUBLEJUMPEND,
//    R_JUMPL,
//    R_JUMPLEND,
//    R_SLIDE,
//    R_WALLJUMP,
//    R_JUMPEND,
//    R_DOUBLEBACKFLIP,
//    R_JUMPEND,
//    R_BEND,
//    R_BENDEND,
//    R_KICK
//};

#endif
