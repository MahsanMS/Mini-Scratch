#ifndef MINI_SCRATCH_EVENTS_H
#define MINI_SCRATCH_EVENTS_H

#include "UI.h"
bool GreenFlag=false;
bool Space=false;
bool Up=false;
bool Right=false;
bool Down=false;
bool Left=false;

void check_green(Sprite &sp) {
    sp.is_running=GreenFlag;
}
void check_down(Sprite &sp) {
    sp.is_running=Down;
}
void check_right(Sprite &sp) {
    sp.is_running=Right;
}
void check_left(Sprite &sp) {
    sp.is_running=Left;
}
void check_up(Sprite &sp) {
    sp.is_running=Up;
}
void check_space(Sprite &sp) {
    sp.is_running=Space;
}
void check_sprite_clicked(Sprite &sp) {
    sp.is_running=sp.sprite_clicked;
}

#endif