#ifndef MINI_SCRATCH_VARIABLES_H
#define MINI_SCRATCH_VARIABLES_H

#include "UI.h"

void set_var_to(Sprite &sprite,std::string nameofvar,float f) {
    sprite.var[nameofvar] = f;
}

void change_var_by(Sprite &sprite,std::string nameofvar,float f) {
    sprite.var[nameofvar]+= f;
}

#endif