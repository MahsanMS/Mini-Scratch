#ifndef MINI_SCRATCH_CONTROL_H
#define MINI_SCRATCH_CONTROL_H

#include "UI.h"

void handle_if(Sprite &s,int index,bool condition) {


    while(!(s.blocks.blocks[index].block_id.general_type==CONT&&s.blocks.blocks[index].block_id.control_mode==ENDIF)&&index<s.blocks.blocks.size()) {
        s.blocks.blocks[index].parent_id = condition;
        index++;
    }
}
void handle_else_if(Sprite &s,int index,bool condition) {

    while(!(s.blocks.blocks[index].block_id.general_type==CONT&&s.blocks.blocks[index].block_id.control_mode==ELSE)&&index<s.blocks.blocks.size()) {
        s.blocks.blocks[index].parent_id = condition;
        index++;
    }
    while(!(s.blocks.blocks[index].block_id.general_type==CONT&&s.blocks.blocks[index].block_id.control_mode==ENDELSE)&&index<s.blocks.blocks.size()) {
        s.blocks.blocks[index].parent_id = !condition;
        index++;
    }
}
void handle_repeat(Sprite &s,int index,int repeat) {

    std::vector<Block> copy;
    int init=index;


    while(!(s.blocks.blocks[index].block_id.general_type==CONT&&s.blocks.blocks[index].block_id.control_mode==ENDREPEAT)&&index<s.blocks.blocks.size()) {
        copy.pushback(s.blocks.blocks[index]);
        index++;
    }
    int n=copy.size();

    for(int i=1;i<repeat;i++)
    {
        copy.insert(copy.end(),copy.begin(),copy.end());

    }
    s.blocks.blocks.insert(init+n,copy.begin(),copy.end());
}

#endif