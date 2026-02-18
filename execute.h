#ifndef MINI_SCRATCH_EXECUTE_H
#define MINI_SCRATCH_EXECUTE_H

#include "UI.h"
#include "motion.h"
#include "looks.h"

void executeBlock(Sprite &sprite,Block & block,Stage &stage) {
    switch (block.block_id.general_type) {
        case MOTION:{
            switch (block.block_id.id_number) {
                //move steps
                    case 0: {
                        float steps=std::stof(block.inputs[0].line.text);
                        move(&sprite,steps);
                        break;
                    }
                    //turn right
                    case 1: {
                        float deg=std::stof(block.inputs[0].line.text);
                        right_turn(&sprite,deg);
                        break;
                    }
                    //turn left
                    case 2: {
                        float deg=std::stof(block.inputs[0].line.text);
                        left_turn(&sprite,deg);
                        break;

                    }
                    //change x by
                    case 3: {
                        float deltaX=std::stof(block.inputs[0].line.text);
                        change_x_by(&sprite,deltaX);
                        break;
                    }
                    // case 4:{}
                    //change y by
                    case 5: {
                        float deltaY=std::stof(block.inputs[0].line.text);
                        change_y_by(&sprite,deltaY);
                        break;

                    }
                    // case 6:{}
                    //go to random
                    case 7: {
                        go_to_random_position(&sprite);
                        break;
                    }
                    //go to mouse
                   // case 8:{}
            }
              break;}
        case LOOKS: {

            switch (block.block_id.id_number) {

                case 0: {
                    switch_to_next_costum(sprite);

                    break;
                }

                case 1: {
                    next_backdrop(stage);
                    break;
                }

                case 2: {
                    int indx=std::stoi(block.inputs[0].line.text);
                    switch_to_custom(sprite,indx);
                    break;

                }

                case 3: {
                    int indx=std::stoi(block.inputs[0].line.text);
                    switch_to_backdrop(stage,indx);
                    break;
                }

                case 4: {
                    std::string text=block.inputs[0].line.text;
                    int time=std::stoi(block.inputs[1].line.text);
                    say_for(sprite,text,time);
                    break;

                }

                case 5: {

                    break;
                }

            }
          break;
        }
        case SOUND: {

            break;
        }
            //isrunng changes
        case EVENT: {
            break;
        }
            //if -   repeat remains
        case CONT: {
            break;
        }
            //remains
        case SENSE: {
            break;
        }
            //remains->operators raw file
        case OP: {
            break;
        }
            //remains
        case VAR: {
            break;
        }
            //remains
        case FUNC: {
            break;
        }
    }
}
void exec_sprites(std::vector<Sprite> &sp,Stage& stage) {
    for (auto s : sp) {
        if (!s.is_running) continue;
        if (s.current_block>=s.blocks.blocks.size()) {
            s.is_running = false;
        }
        Block &b = s.blocks.blocks[s.current_block];
        if (!b.parent_id) continue;

        executeBlock(s,b,stage);
    }
}

#endif