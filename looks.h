#ifndef MINI_SCRATCH_LOOKS_H
#define MINI_SCRATCH_LOOKS_H

#include "UI.h"

void switch_to_next_costum(Sprite &sprite) {
    sprite.current_custom = (sprite.current_custom + 1) % sprite.custom_manager.customs.size();
}

void next_backdrop(Stage & stage) {
    if (!stage.backdrops.empty()) {
        stage.current_backdrop = (stage.current_backdrop + 1) % stage.backdrops.size();
    }
}

void switch_to_custom(Sprite &sprite,int indx) {
    sprite.current_custom=indx;
}

void switch_to_backdrop(Stage & stage,int indx) {
    if (!stage.backdrops.empty()) {
        stage.current_backdrop=indx;
    }
}

void say_for(Sprite &sprite,std::string text,int time) {
    sprite.saytext=text;
    sprite.say_time=time;
}

void think_for(Sprite &sprite,std::string text,int time) {
    sprite.thinktext=text;
    sprite.think_time=time;
}

void say(Sprite &sprite,std::string text) {
    sprite.saytext=text;
    sprite.say_time=-1;
}

void think(Sprite &sprite,std::string text) {
    sprite.thinktext=text;
    sprite.think_time=-1;
}

void update_sprite(Sprite &sprite) {
    if (sprite.say_time>0)
        sprite.say_time--;
    if (sprite.think_time>0)
        sprite.think_time--;
}

void change_size_to(Sprite &sprite,float val) {
    sprite.state.size+=val;
    if (sprite.state.size<1) {
        sprite.state.size=1;
    }
}

void set_size_to(Sprite &sprite,float val) {
    sprite.state.size=val;
    if (sprite.state.size<1) {
        sprite.state.size=1;
    }
}

#endif