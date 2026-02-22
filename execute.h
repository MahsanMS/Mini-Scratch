#ifndef MINI_SCRATCH_EXECUTE_H
#define MINI_SCRATCH_EXECUTE_H

#include "UI.h"
#include "motion.h"
#include "looks.h"
#include "variables.h"
#include "control.h"

SpriteManager sprite_manager;

void executeBlock(Sprite &sprite,Block & block) {
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
                    //go to
                      case 3: {
                        float targetX=std::stof(block.inputs[0].line.text);
                        float targetY=std::stof(block.inputs[1].line.text);
                        go_to( &sprite, targetX,  targetY);
                        break;
                              }
                    //set direction
                    case 4: {
                        float newdirection=std::stof(block.inputs[0].line.text);
                        set_direction(&sprite,  newdirection);
                        break;
                    }
                    //change x by
                    case 5: {
                        float deltaX=std::stof(block.inputs[0].line.text);
                        change_x_by(&sprite,deltaX);
                    }
                    //change y by
                    case 6: {
                        float deltaY=std::stof(block.inputs[0].line.text);
                        change_y_by(&sprite,deltaY);
                        break;

                    }

                    //go to random
                    case 7: {
                        go_to_random_position(&sprite);
                        break;
                    }
                    //go to mouse
                   case 8:{
                       int x,y;
                   SDL_GetMouseState(&x,&y);
                        go_to( &sprite, x,  y);
                   }
                    //step on edge
                     case 9: {
                        stop_on_edge(& sprite);
                        break;
                        }
            }
              break;}
        case LOOKS: {

            switch (block.block_id.id_number) {

                case 0: {
                    switch_to_next_costum(sprite);

                    break;
                }

                // case 1: {
                //     next_backdrop(stage);
                //     break;
                // }

                case 2: {
                    int indx=std::stoi(block.inputs[0].line.text);
                    switch_to_custom(sprite,indx);
                    break;

                }

                // case 3: {
                //     int indx=std::stoi(block.inputs[0].line.text);
                //     switch_to_backdrop(stage,indx);
                //     break;
                // }

                case 4: {
                    std::string text=block.inputs[0].line.text;
                    int time=std::stoi(block.inputs[1].line.text);
                    say_for(sprite,text,time);
                    break;

                }

                case 5: {
                    std::string text=block.inputs[0].line.text;
                    int time=std::stoi(block.inputs[1].line.text);
                    think_for(sprite,text,time);

                    break;
                }
                case 6: {
                    std::string text=block.inputs[0].line.text;
                    say(sprite, text) ;


                    break;
                }
                case 7: {
                    std::string text=block.inputs[0].line.text;
                    think(sprite,text);
                    break;
                }
                case 8: {
                    float val=std::stof(block.inputs[0].line.text);
                    change_size_to(sprite, val);
                    break;
                }
                case 9: {
                    float val=std::stof(block.inputs[0].line.text);
                    change_size_to(sprite, val);
                    break;
                }
            }
          break;
        }
            //isrunng changes
        case EVENT: {

            switch (block.block_id.id_number) {

                case 0: {
                    check_green( sprite);
                    break;
                }

                case 4: {
                    check_right(sprite );
                    break;
                }

                case 5: {
                    check_left(sprite );
                    break;

                }

                case 2: {
                    check_up(sprite);
                    break;
                }

                case 3: {
                    check_down(sprite );
                    break;

                }

                case 1: {
                    check_space(sprite );
                    break;

                }

                case 6: {
                    check_sprite_clicked(sprite );

                    break;
                }

            }
            break;
        }
        // case OP: {
        //     switch (block.block_id.id_number) {
        //
        //         case 0: {
        //           float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.f_value=sum(a,b);
        //             break;
        //         }
        //
        //         case 1: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.f_value=subtract(a,b);
        //             break;
        //         }
        //
        //         case 2: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.f_value=multiply(a,b);
        //             break;
        //
        //         }
        //
        //         case 3: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.f_value= divide(a,b);
        //             break;
        //         }
        //
        //         case 4: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.f_value=remainder(a,b);
        //
        //             break;
        //
        //         }
        //
        //         case 5: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             block.f_value=absolute(a);
        //             break;
        //         }
        //         case 6: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             block.f_value=square_root(a);
        //             break;
        //         }
        //         case 7: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             block.f_value=floor(a);
        //             break;
        //         }
        //         case 8: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             block.f_value=ceil(a);
        //             break;
        //         }
        //         case 9: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             block.f_value=sin(a);
        //             break;
        //         }
        //         case 10: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             block.f_value=cos(a);
        //             break;
        //         }
        //             //logical
        //         case 11: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.b_value=less_than(a,b);
        //             break;
        //         }
        //         case 12: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.b_value=greater_than(a,b);
        //             break;
        //         }
        //         case 13: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.b_value=equal(a,b);
        //             break;
        //         }
        //         case 14: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.b_value=less_or_equal(a,b);
        //             break;
        //         }
        //         case 15: {
        //             float a=std::stof(block.inputs[0].line.text);
        //             float b=std::stof(block.inputs[0].line.text);
        //             block.b_value=greater_or_equal(a,b);
        //             break;
        //         }
        //             //
        //         case 16: {
        //             int a=std::stoi(block.inputs[0].line.text);
        //             int b=std::stoi(block.inputs[0].line.text);
        //             block.b_value=logical_and(a,b);
        //             break;
        //         }
        //         case 17: {
        //             int a=std::stoi(block.inputs[0].line.text);
        //             int b=std::stoi(block.inputs[0].line.text);
        //             block.b_value=logical_or( a, b);
        //             break;
        //         }
        //         case 18: {
        //             int a=std::stoi(block.inputs[0].line.text);
        //             block.b_value= logical_not( a);
        //             break;
        //         }
        //         case 19: {
        //             int a=std::stoi(block.inputs[0].line.text);
        //             int b=std::stoi(block.inputs[0].line.text);
        //             block.b_value=logical_xor( a, b);
        //             break;
        //         }
        //         case 20: {
        //             int a=std::stoi(block.inputs[0].line.text);
        //             int b=std::stoi(block.inputs[0].line.text);
        //             block.b_value=logical_xor( a, b);
        //             break;
        //         }
        //         case 21: {
        //             int a=std::stoi(block.inputs[0].line.text);
        //             int b=std::stoi(block.inputs[0].line.text);
        //             block.b_value=logical_xor( a, b);
        //             break;
        //         }
        //         case 22: {
        //             int a=std::stoi(block.inputs[0].line.text);
        //             int b=std::stoi(block.inputs[0].line.text);
        //             block.b_value=logical_xor( a, b);
        //             break;
        //         }
        //     }
        //     break;
        // }

        case VAR: {

            switch (block.block_id.id_number) {

                case 0: {
                  std::string nameofvar=block.inputs[0].line.text;
                    float f=stof(block.inputs[1].line.text);
                    set_var_to(sprite,nameofvar,f);
                    break;
                }

                case 1: {
                    std::string nameofvar=block.inputs[0].line.text;
                    float f=stof(block.inputs[1].line.text);
                   change_var_by(sprite,nameofvar,f);
                    break;
                }
            }
            break;
        }
    }
}
void exec_sprites(Sprite sp[50],SDL_Event& e) {
    for (int i = 0; i < sprite_manager.sprites.size(); i++){
        auto& s = sp[i];
        s.manage_event(e);
        if (!s.is_running) continue;
        if (s.current_block>=s.blocks.blocks.size()) {
            s.is_running = false;
        }
        Block &b = s.blocks.blocks[s.current_block];
        if (!b.parent_id) continue;

        if (s.blocks.blocks[s.current_block].parent_id)
        {
            executeBlock(s,b);
        }

        //if
        if (s.blocks.blocks[s.current_block].block_id.general_type==CONT&&s.blocks.blocks[s.current_block].block_id.control_mode==IF) {
            int condition =std::stoi(s.blocks.blocks[s.current_block].inputs[0].line.text);
            handle_if(s,s.current_block++,condition);
                 s.current_block++;
        }
        //if-else
        if (s.blocks.blocks[s.current_block].block_id.general_type==CONT&&s.blocks.blocks[s.current_block].block_id.control_mode==IFELSE) {
            int condition =std::stoi(s.blocks.blocks[s.current_block].inputs[0].line.text);
            handle_else_if(s,s.current_block++,condition);
            s.current_block++;
        }
        //repeat
        // if (s.blocks.blocks[s.current_block].block_id.general_type==CONT&&s.blocks.blocks[s.current_block].block_id.control_mode==REPEAT) {
        //     int repeat =std::stoi(s.blocks.blocks[s.current_block].inputs[0].line.text);
        //     handle_repeat(s,s.current_block++, repeat);
        //     s.current_block++;
        // }
        s.current_block++;

    }
}

void executeProgram(Sprite sp[50],SDL_Event& e) {
    bool running =false;
    exec_sprites(sp,e);

    if (GreenFlag||Space||Up||Right||Down||Left) running=true;
    while (running) {
        bool runfalse=true;
        for (int i = 0; i < sprite_manager.sprites.size(); i++){
            auto& s = sp[i];
            cout << i << ' ' << s.is_running << endl;
            if (s.is_running==0)
            {
                runfalse = false;
            }
        }

        exec_sprites(sp,e);

        if (runfalse==false)
            running=false;
    }
}

#endif