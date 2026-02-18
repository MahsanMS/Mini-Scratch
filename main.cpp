#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_ttf.h>
#include "UI.h"

using namespace std;
SDL_DisplayMode DM;
int count;

int tab_page = 0;
void go_to_code_tab() {tab_page = 0;}

OriginalBlocksManager all_original_managers[5];
int motion_index = 0;
int looks_index = 1;
int events_index = 2;
int control_index = 3;
int operators_index = 4;
int original_manager_page = 0;

void code_motion() {original_manager_page = motion_index;}
void add_motion_blocks(TTF_Font*);

void code_looks() {original_manager_page = looks_index;}
void add_looks_blocks(TTF_Font*);

void code_events() {original_manager_page = events_index;}
void add_events_blocks(TTF_Font*);

void code_control() {original_manager_page = control_index;}
void add_control_blocks(TTF_Font*);

void code_operators() {original_manager_page = operators_index;}
void add_operators_blocks(TTF_Font*);

void f() {}

void go_up_original() {all_original_managers[original_manager_page].go_up();}
void go_down_original() {all_original_managers[original_manager_page].go_down();}

int main(int argc, char * argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_StartTextInput();

    SDL_GetCurrentDisplayMode(0, &DM);

    SDL_Window* window = SDL_CreateWindow("Mini Scratch!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        DM.w * 0.975, DM.h * 0.89, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    bool running = true;

    TTF_Font* font = TTF_OpenFont("assests\\font\\CascadiaCode.ttf", 15);
    if (font == nullptr)
    {
        cout << "Font not found..." << endl;
        return 0;
    }

    Button code_button(0.015 * DM.w, 0.01 * DM.h, 0.075 * DM.w, 0.04 * DM.h, 7);
    code_button.callback = &go_to_code_tab;

    // custome tabs will be added later

    // motion button
    Button motion_code_button(0, 0.05 * DM.h * (motion_index + 1), 0.035 * DM.w, 0.05 * DM.h, 10);
    motion_code_button.set_button_RGBA(0, 153, 255, 255);
    motion_code_button.set_hover_RGBA(127, 187, 227, 255);
    motion_code_button.set_active_RGBA(0, 80, 133, 255);
    motion_code_button.callback = &code_motion;

    // looks button
    Button looks_code_button(0, 0.05 * DM.h * (looks_index + 1), 0.035 * DM.w, 0.05 * DM.h, 10);
    looks_code_button.set_button_RGBA(148, 3, 252, 255);
    looks_code_button.set_hover_RGBA(208, 143, 255, 255);
    looks_code_button.set_active_RGBA(71, 0, 122, 255);
    looks_code_button.callback = &code_looks;

    // events button
    Button events_code_button(0, 0.05 * DM.h * (events_index + 1), 0.035 * DM.w, 0.05 * DM.h, 10);
    events_code_button.set_button_RGBA(255, 255, 0, 255);
    events_code_button.set_hover_RGBA(255, 255, 115, 255);
    events_code_button.set_active_RGBA(128, 128, 0, 255);
    events_code_button.callback = &code_events;

    // control button
    Button control_code_button(0, 0.05 * DM.h * (control_index + 1), 0.035 * DM.w, 0.05 * DM.h, 10);
    control_code_button.set_button_RGBA(255, 145, 0, 255);
    control_code_button.set_hover_RGBA(255, 175, 71, 255);
    control_code_button.set_active_RGBA(150, 85, 0, 255);
    control_code_button.callback = &code_control;

    // operators button
    Button operator_code_button(0, 0.05 * DM.h * (operators_index + 1), 0.035 * DM.w, 0.05 * DM.h, 10);
    operator_code_button.set_button_RGBA(2, 168, 21, 255);
    operator_code_button.set_hover_RGBA(59, 235, 79, 255);
    operator_code_button.set_active_RGBA(0, 77, 9, 255);
    operator_code_button.callback = &code_operators;

    ::count = DM.h * 0.83 / 35;

    // OriginalBlocksManager original_blocks_manager(0.037 * DM.w, 0.053 * DM.h, 0.175 * DM.w, 0.83 * DM.h, count);
    add_motion_blocks(font);
    add_looks_blocks(font);
    add_events_blocks(font);
    add_control_blocks(font);
    add_operators_blocks(font);

    // go up and down buttons
    Button go_up_original_button(0.218 * DM.w, 0.06 * DM.h, 18, 18, 10);
    go_up_original_button.callback = &go_up_original;
    Button go_down_original_button(0.218 * DM.w, 0.85 * DM.h, 18, 18, 10);
    go_down_original_button.callback = &go_down_original;

    BlockManager manager(0.239 * DM.w, 0.053 * DM.h, 0.425 * DM.w, 0.83 * DM.h, ::count); // will change to Sprite's manager later

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                    break;
                }
            }

            // managers
            all_original_managers[original_manager_page].manage_event(event, manager, font);
            manager.manage_event(event);

            // buttons
            code_button.manage_event(event);

            motion_code_button.manage_event(event);
            looks_code_button.manage_event(event);
            events_code_button.manage_event(event);
            control_code_button.manage_event(event);
            operator_code_button.manage_event(event);

            go_up_original_button.manage_event(event);
            go_down_original_button.manage_event(event);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // managers
        all_original_managers[original_manager_page].render(renderer, font);
        manager.render(renderer, font);

        //buttons
        code_button.render(renderer);

        motion_code_button.render(renderer);
        looks_code_button.render(renderer);
        events_code_button.render(renderer);
        control_code_button.render(renderer);
        operator_code_button.render(renderer);

        go_up_original_button.render(renderer);
        go_down_original_button.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_Quit();
    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void add_motion_blocks(TTF_Font* font)
{
    // motion blocks
    all_original_managers[motion_index] = OriginalBlocksManager(0.037 * DM.w, 0.053 * DM.h, 0.2 * DM.w, 0.83 * DM.h, ::count);

    // motion/move
    Block* move_block = new Block();
    move_block -> set_block_RGBA(0, 153, 255, 255);
    move_block -> set_ghost_RGBA(127, 187, 227, 255);
    move_block -> add_text("move", font);
    move_block -> add_input();

    move_block -> block_id.general_type = MOTION;
    move_block -> block_id.id_number = 0;
    all_original_managers[motion_index].add_original_block(*move_block);
    delete move_block;

    // motion/turn_right
    Block* turn_right_block = new Block();
    turn_right_block -> set_block_RGBA(0, 153, 255, 255);
    turn_right_block -> set_ghost_RGBA(127, 187, 227, 255);
    turn_right_block -> add_text("turn right", font);
    turn_right_block -> add_input();
    turn_right_block -> add_text("degrees", font);

    turn_right_block -> block_id.general_type = MOTION;
    turn_right_block -> block_id.id_number = 1;
    all_original_managers[motion_index].add_original_block(*turn_right_block);
    delete turn_right_block;

    // motion/turn_left
    Block* turn_left_block = new Block();
    turn_left_block -> set_block_RGBA(0, 153, 255, 255);
    turn_left_block -> set_ghost_RGBA(127, 187, 227, 255);
    turn_left_block -> add_text("turn left", font);
    turn_left_block -> add_input();
    turn_left_block -> add_text("degrees", font);

    turn_left_block -> block_id.general_type = MOTION;
    turn_left_block -> block_id.id_number = 2;
    all_original_managers[motion_index].add_original_block(*turn_left_block);
    delete turn_left_block;

    // motion/go_to
    Block* go_to_block = new Block();
    go_to_block -> set_block_RGBA(0, 153, 255, 255);
    go_to_block -> set_ghost_RGBA(127, 187, 227, 255);
    go_to_block -> add_text("go to x:", font);
    go_to_block -> add_input();
    go_to_block -> add_text("y:", font);
    go_to_block -> add_input();

    go_to_block -> block_id.general_type = MOTION;
    go_to_block -> block_id.id_number = 3;
    all_original_managers[motion_index].add_original_block(*go_to_block);
    delete go_to_block;

    // motion/set_direction
    Block* set_direction_block = new Block();
    set_direction_block -> set_block_RGBA(0, 153, 255, 255);
    set_direction_block -> set_ghost_RGBA(127, 187, 227, 255);
    set_direction_block -> add_text("set direction to", font);
    set_direction_block -> add_input();

    set_direction_block -> block_id.general_type = MOTION;
    set_direction_block -> block_id.id_number = 4;
    all_original_managers[motion_index].add_original_block(*set_direction_block);
    delete set_direction_block;

    // motion/change_x_by
    Block* change_x_block = new Block();
    change_x_block -> set_block_RGBA(0, 153, 255, 255);
    change_x_block -> set_ghost_RGBA(127, 187, 227, 255);
    change_x_block -> add_text("change x by", font);
    change_x_block -> add_input();

    change_x_block -> block_id.general_type = MOTION;
    change_x_block -> block_id.id_number = 5;
    all_original_managers[motion_index].add_original_block(*change_x_block);
    delete change_x_block;

    // motion/change_y_by
    Block* change_y_block = new Block();
    change_y_block -> set_block_RGBA(0, 153, 255, 255);
    change_y_block -> set_ghost_RGBA(127, 187, 227, 255);
    change_y_block -> add_text("change y by", font);
    change_y_block -> add_input();

    change_y_block -> block_id.general_type = MOTION;
    change_y_block -> block_id.id_number = 6;
    all_original_managers[motion_index].add_original_block(*change_y_block);
    delete change_y_block;

    // motion/go_to_random_position
    Block* go_random_block = new Block();
    go_random_block -> set_block_RGBA(0, 153, 255, 255);
    go_random_block -> set_ghost_RGBA(127, 187, 227, 255);
    go_random_block -> add_text("go to random position", font);

    go_random_block -> block_id.general_type = MOTION;
    go_random_block -> block_id.id_number = 7;
    all_original_managers[motion_index].add_original_block(*go_random_block);
    delete go_random_block;

    // motion/go_to_mouse_position
    Block* mouse_position_block = new Block();
    mouse_position_block -> set_block_RGBA(0, 153, 255, 255);
    mouse_position_block -> set_ghost_RGBA(127, 187, 227, 255);
    mouse_position_block -> add_text("go to mouse position", font);

    mouse_position_block -> block_id.general_type = MOTION;
    mouse_position_block -> block_id.id_number = 8;
    all_original_managers[motion_index].add_original_block(*mouse_position_block);
    delete mouse_position_block;

    // motion/stop_on_edge
    Block* stop_on_edge_block = new Block();
    stop_on_edge_block -> set_block_RGBA(0, 153, 255, 255);
    stop_on_edge_block -> set_ghost_RGBA(127, 187, 227, 255);
    stop_on_edge_block -> add_text("stop one edge", font);

    stop_on_edge_block -> block_id.general_type = MOTION;
    stop_on_edge_block -> block_id.id_number = 9;
    all_original_managers[motion_index].add_original_block(*stop_on_edge_block);
    delete stop_on_edge_block;
}

void add_looks_blocks(TTF_Font* font)
{
    // looks blocks
    all_original_managers[looks_index] = OriginalBlocksManager(0.037 * DM.w, 0.053 * DM.h, 0.2 * DM.w, 0.83 * DM.h, ::count);

    // looks/next_custome
    Block* next_custome_block = new Block();
    next_custome_block -> set_block_RGBA(148, 3, 252, 255);
    next_custome_block -> set_ghost_RGBA(208, 143, 255, 255);
    next_custome_block -> add_text("next custome", font);

    next_custome_block -> block_id.general_type = LOOKS;
    next_custome_block -> block_id.id_number = 0;
    all_original_managers[looks_index].add_original_block(*next_custome_block);
    delete next_custome_block;

    // looks/next_backdrop
    Block* next_backdrop_block = new Block();
    next_backdrop_block -> set_block_RGBA(148, 3, 252, 255);
    next_backdrop_block -> set_ghost_RGBA(208, 143, 255, 255);
    next_backdrop_block -> add_text("next backdrop", font);

    next_backdrop_block -> block_id.general_type = LOOKS;
    next_backdrop_block -> block_id.id_number = 1;
    all_original_managers[looks_index].add_original_block(*next_backdrop_block);
    delete next_backdrop_block;

    // looks/switch_custome_to
    Block* switch_custome_block = new Block();
    switch_custome_block -> set_block_RGBA(148, 3, 252, 255);
    switch_custome_block -> set_ghost_RGBA(208, 143, 252, 255);
    switch_custome_block -> add_text("switch custome number to", font);
    switch_custome_block -> add_input();

    switch_custome_block -> block_id.general_type = LOOKS;
    switch_custome_block -> block_id.id_number = 2;
    all_original_managers[looks_index].add_original_block(*switch_custome_block);
    delete switch_custome_block;

    // looks/switch_backdrop_to
    Block* switch_backdrop_block = new Block();
    switch_backdrop_block -> set_block_RGBA(148, 3, 252, 255);
    switch_backdrop_block -> set_ghost_RGBA(208, 143, 255, 255);
    switch_backdrop_block -> add_text("switch backdrop number to", font);
    switch_backdrop_block -> add_input();

    switch_backdrop_block -> block_id.general_type = LOOKS;
    switch_backdrop_block -> block_id.id_number = 3;
    all_original_managers[looks_index].add_original_block(*switch_backdrop_block);
    delete switch_backdrop_block;

    // looks/say_for
    Block* say_for_block = new Block();
    say_for_block -> set_block_RGBA(148, 3, 252, 255);
    say_for_block -> set_ghost_RGBA(208, 143, 255, 255);
    say_for_block -> add_text("say", font);
    say_for_block -> add_input();
    say_for_block -> add_text("for", font);
    say_for_block -> add_input();
    say_for_block -> add_text("seconds", font);

    say_for_block -> block_id.general_type = LOOKS;
    say_for_block -> block_id.id_number = 4;
    all_original_managers[looks_index].add_original_block(*say_for_block);
    delete say_for_block;

    // looks/think_for
    Block* think_for_block = new Block();
    think_for_block -> set_block_RGBA(148, 3, 252, 255);
    think_for_block -> set_ghost_RGBA(208, 143, 255, 255);
    think_for_block -> add_text("think", font);
    think_for_block -> add_input();
    think_for_block -> add_text("for", font);
    think_for_block -> add_input();
    think_for_block -> add_text("seconds", font);

    think_for_block -> block_id.general_type = LOOKS;
    think_for_block -> block_id.id_number = 5;
    all_original_managers[looks_index].add_original_block(*think_for_block);
    delete think_for_block;

    // looks/say
    Block* say_block = new Block();
    say_block -> set_block_RGBA(148, 3, 252, 255);
    say_block -> set_ghost_RGBA(208, 143, 255, 255);
    say_block -> add_text("say", font);
    say_block -> add_input();

    say_block -> block_id.general_type = LOOKS;
    say_block -> block_id.id_number = 6;
    all_original_managers[looks_index].add_original_block(*say_block);
    delete say_block;

    // looks/think
    Block* think_block = new Block();
    think_block -> set_block_RGBA(148, 3, 252, 255);
    think_block -> set_ghost_RGBA(208, 143, 255, 255);
    think_block -> add_text("think", font);
    think_block -> add_input();

    think_block -> block_id.general_type = LOOKS;
    think_block -> block_id.id_number = 7;
    all_original_managers[looks_index].add_original_block(*think_block);
    delete think_block;

    // looks/change_size_by
    Block* change_size_block = new Block();
    change_size_block -> set_block_RGBA(148, 3, 252, 255);
    change_size_block -> set_ghost_RGBA(208, 143, 255, 255);
    change_size_block -> add_text("change size by", font);
    change_size_block -> add_input();

    change_size_block -> block_id.general_type = LOOKS;
    change_size_block -> block_id.id_number = 8;
    all_original_managers[looks_index].add_original_block(*change_size_block);
    delete change_size_block;

    // looks/set_size_to
    Block* set_size_block = new Block();
    set_size_block -> set_block_RGBA(148, 3, 252, 255);
    set_size_block -> set_ghost_RGBA(208, 143, 255, 255);
    set_size_block -> add_text("set size to", font);
    set_size_block -> add_input();

    set_size_block -> block_id.general_type = LOOKS;
    set_size_block -> block_id.id_number = 9;
    all_original_managers[looks_index].add_original_block(*set_size_block);
    delete set_size_block;
}

void add_events_blocks(TTF_Font* font)
{
    // events blocks
    all_original_managers[events_index] = OriginalBlocksManager(0.037 * DM.w, 0.053 * DM.h, 0.2 * DM.w, 0.83 * DM.h, ::count);

    // events/green_flag
    Block* green_flag_block = new Block();
    green_flag_block -> set_block_RGBA(255, 255, 0, 255);
    green_flag_block -> set_ghost_RGBA(255, 255, 115, 255);
    green_flag_block -> add_text("when green flag preseed", font);

    green_flag_block -> block_id.general_type = EVENT;
    green_flag_block -> block_id.id_number = 0;
    all_original_managers[events_index].add_original_block(*green_flag_block);
    delete green_flag_block;

    // events/space
    Block* space_block = new Block();
    space_block -> set_block_RGBA(255, 255, 0, 255);
    space_block -> set_ghost_RGBA(255, 255, 115, 255);
    space_block -> add_text("when space pressed", font);

    space_block -> block_id.general_type = EVENT;
    space_block -> block_id.id_number = 1;
    all_original_managers[events_index].add_original_block(*space_block);
    delete space_block;

    // event/up
    Block* up_block = new Block();
    up_block -> set_block_RGBA(255, 255, 0, 255);
    up_block -> set_ghost_RGBA(255, 255, 115, 255);
    up_block -> add_text("when ↑ pressed", font);

    up_block -> block_id.general_type = EVENT;
    up_block -> block_id.id_number = 2;
    all_original_managers[events_index].add_original_block(*up_block);
    delete up_block;

    // events/down
    Block* down_block = new Block();
    down_block -> set_block_RGBA(255, 255, 0, 255);
    down_block -> set_ghost_RGBA(255, 255, 115, 255);
    down_block -> add_text("when ↓ pressed", font);

    down_block -> block_id.general_type = EVENT;
    down_block -> block_id.id_number = 3;
    all_original_managers[events_index].add_original_block(*down_block);
    delete down_block;

    // events/right
    Block* right_block = new Block();
    right_block -> set_block_RGBA(255, 255, 0, 255);
    right_block -> set_ghost_RGBA(255, 255, 115, 255);
    right_block -> add_text("when → pressed", font);

    right_block -> block_id.general_type = EVENT;
    right_block -> block_id.id_number = 4;
    all_original_managers[events_index].add_original_block(*right_block);
    delete right_block;

    // events/left
    Block* left_block = new Block();
    left_block -> set_block_RGBA(255, 255, 0, 255);
    left_block -> set_ghost_RGBA(255, 255, 115, 255);
    left_block -> add_text("when ← pressed", font);

    left_block -> block_id.general_type = EVENT;
    left_block -> block_id.id_number = 5;
    all_original_managers[events_index].add_original_block(*left_block);
    delete left_block;
}

void add_control_blocks(TTF_Font* font)
{
    // control blocks
    all_original_managers[control_index] = OriginalBlocksManager(0.037 * DM.w, 0.053 * DM.h, 0.2 * DM.w, 0.83 * DM.h, ::count);

    // control/if
    Block* if_block = new Block();
    if_block -> set_block_RGBA(255, 145, 0, 255);
    if_block -> set_ghost_RGBA(255, 175, 71, 255);
    if_block -> add_text("if", font);

    if_block -> block_id.general_type = CONT;
    if_block -> block_id.id_number = 0;
    all_original_managers[control_index].add_original_block(*if_block);
    delete if_block;

    // control/if_else
    Block* if_else_block = new Block();
    if_else_block -> set_block_RGBA(255, 145, 0, 255);
    if_else_block -> set_ghost_RGBA(255, 175, 71, 255);
    if_else_block -> add_text("if-else", font);

    if_else_block -> block_id.general_type = CONT;
    if_else_block -> block_id.id_number = 1;
    all_original_managers[control_index].add_original_block(*if_else_block);
    delete if_else_block;

    // control/repeat
    Block* repeat_block = new Block();
    repeat_block -> set_block_RGBA(255, 145, 0, 255);
    repeat_block -> set_ghost_RGBA(255, 175, 71, 255);
    repeat_block -> add_text("repeat", font);
    repeat_block -> add_input();
    repeat_block -> add_text("times", font);

    repeat_block -> block_id.general_type = CONT;
    repeat_block -> block_id.id_number = 2;
    all_original_managers[control_index].add_original_block(*repeat_block);
    delete repeat_block;
}

void add_operators_blocks(TTF_Font* font)
{
    // operators blocks
    all_original_managers[operators_index] = OriginalBlocksManager(0.037 * DM.w, 0.053 * DM.h, 0.2 * DM.w, 0.83 * DM.h, ::count);

    // operators/sum
    Block* sum_block = new Block();
    sum_block -> set_block_RGBA(2, 168, 21, 255);
    sum_block -> set_ghost_RGBA(59, 235, 79, 255);
    sum_block -> add_input();
    sum_block -> add_text("+", font);
    sum_block -> add_input();

    sum_block -> block_id.general_type = OP;
    sum_block -> block_id.id_number = 0;
    all_original_managers[operators_index].add_original_block(*sum_block);
    delete sum_block;

    // operators/subtract
    Block* subtract_block = new Block();
    subtract_block -> set_block_RGBA(2, 168, 21, 255);
    subtract_block -> set_ghost_RGBA(59, 235, 79, 255);
    subtract_block -> add_input();
    subtract_block -> add_text("-", font);
    subtract_block -> add_input();

    subtract_block -> block_id.general_type = OP;
    subtract_block -> block_id.id_number = 1;
    all_original_managers[operators_index].add_original_block(*subtract_block);
    delete subtract_block;

    // operators/multiply
    Block* multiply_block = new Block();
    multiply_block -> set_block_RGBA(2, 168, 21, 255);
    multiply_block -> set_ghost_RGBA(59, 235, 79, 255);
    multiply_block -> add_input();
    multiply_block -> add_text("*", font);
    multiply_block -> add_input();

    multiply_block -> block_id.general_type = OP;
    multiply_block -> block_id.id_number = 2;
    all_original_managers[operators_index].add_original_block(*multiply_block);
    delete multiply_block;

    // operators/divide
    Block* divide_block = new Block();
    divide_block -> set_block_RGBA(2, 168, 21, 255);
    divide_block -> set_ghost_RGBA(59, 235, 79, 255);
    divide_block -> add_input();
    divide_block -> add_text("/", font);
    divide_block -> add_input();

    divide_block -> block_id.general_type = OP;
    divide_block -> block_id.id_number = 3;
    all_original_managers[operators_index].add_original_block(*divide_block);
    delete divide_block;

    // operators/mod
    Block* mod_block = new Block();
    mod_block -> set_block_RGBA(2, 168, 21, 255);
    mod_block -> set_ghost_RGBA(59, 235, 79, 255);
    mod_block -> add_input();
    mod_block -> add_text("mod", font);
    mod_block -> add_input();

    mod_block -> block_id.general_type = OP;
    mod_block -> block_id.id_number = 4;
    all_original_managers[operators_index].add_original_block(*mod_block);
    delete mod_block;

    // operators/abs
    Block* abs_block = new Block();
    abs_block -> set_block_RGBA(2, 168, 21, 255);
    abs_block -> set_ghost_RGBA(59, 235, 79, 255);
    abs_block -> add_text("abs", font);
    abs_block -> add_input();

    abs_block -> block_id.general_type = OP;
    abs_block -> block_id.id_number = 5;
    all_original_managers[operators_index].add_original_block(*abs_block);
    delete abs_block;

    // operators/square_root
    Block* square_root_block = new Block();
    square_root_block -> set_block_RGBA(2, 168, 21, 255);
    square_root_block -> set_ghost_RGBA(59, 235, 79, 255);
    square_root_block -> add_text("sqrt", font);
    square_root_block -> add_input();

    square_root_block -> block_id.general_type = OP;
    square_root_block -> block_id.id_number = 6;
    all_original_managers[operators_index].add_original_block(*square_root_block);
    delete square_root_block;

    // oparetors/floor
    Block* floor_block = new Block();
    floor_block -> set_block_RGBA(2, 168, 21, 255);
    floor_block -> set_ghost_RGBA(59, 235, 79, 255);
    floor_block -> add_text("floor", font);
    floor_block -> add_input();

    floor_block -> block_id.general_type = OP;
    floor_block -> block_id.id_number = 7;
    all_original_managers[operators_index].add_original_block(*floor_block);
    delete floor_block;

    // operators/ceil
    Block* ceil_block = new Block();
    ceil_block -> set_block_RGBA(2, 168, 21, 255);
    ceil_block -> set_ghost_RGBA(59, 235, 76, 255);
    ceil_block -> add_text("ceil", font);
    ceil_block -> add_input();

    ceil_block -> block_id.general_type = OP;
    ceil_block -> block_id.id_number = 8;
    all_original_managers[operators_index].add_original_block(*ceil_block);
    delete ceil_block;

    // operators/sin
    Block* sin_block = new Block();
    sin_block -> set_block_RGBA(2, 168, 21, 255);
    sin_block -> set_ghost_RGBA(59, 235, 76, 255);
    sin_block -> add_text("sin", font);
    sin_block -> add_input();
    sin_block -> add_text("°", font);

    sin_block -> block_id.general_type = OP;
    sin_block -> block_id.id_number = 9;
    all_original_managers[operators_index].add_original_block(*sin_block);
    delete sin_block;

    // operators/cos
    Block* cos_block = new Block();
    cos_block -> set_block_RGBA(2, 168, 21, 255);
    cos_block -> set_ghost_RGBA(59, 235, 76, 255);
    cos_block -> add_text("cos", font);
    cos_block -> add_input();
    cos_block -> add_text("°", font);

    cos_block -> block_id.general_type = OP;
    cos_block -> block_id.id_number = 10;
    all_original_managers[operators_index].add_original_block(*cos_block);
    delete cos_block;

    // operators/lower_than
    Block* lower_than_block = new Block();
    lower_than_block -> set_block_RGBA(2, 168, 21, 255);
    lower_than_block -> set_ghost_RGBA(59, 235, 76, 255);
    lower_than_block -> add_input();
    lower_than_block -> add_text("<", font);
    lower_than_block -> add_input();

    lower_than_block -> block_id.general_type = OP;
    lower_than_block -> block_id.id_number = 11;
    all_original_managers[operators_index].add_original_block(*lower_than_block);
    delete lower_than_block;

    // operators/upper_than
    Block* upper_than_block = new Block();
    upper_than_block -> set_block_RGBA(2, 168, 21, 255);
    upper_than_block -> set_ghost_RGBA(59, 235, 76, 255);
    upper_than_block -> add_input();
    upper_than_block -> add_text(">", font);
    upper_than_block -> add_input();

    upper_than_block -> block_id.general_type = OP;
    upper_than_block -> block_id.id_number = 12;
    all_original_managers[operators_index].add_original_block(*upper_than_block);
    delete upper_than_block;

    // operators/equal
    Block* equal_block = new Block();
    equal_block -> set_block_RGBA(2, 168, 21, 255);
    equal_block -> set_ghost_RGBA(59, 235, 76, 255);
    equal_block -> add_input();
    equal_block -> add_text("=", font);
    equal_block -> add_input();

    equal_block -> block_id.general_type = OP;
    equal_block -> block_id.id_number = 13;
    all_original_managers[operators_index].add_original_block(*equal_block);
    delete equal_block;

    // operators/lower_or_equal
    Block* le_block = new Block();
    le_block -> set_block_RGBA(2, 168, 21, 255);
    le_block -> set_ghost_RGBA(59, 235, 76, 255);
    le_block -> add_input();
    le_block -> add_text("<=", font);
    le_block -> add_input();

    le_block -> block_id.general_type = OP;
    le_block -> block_id.id_number = 14;
    all_original_managers[operators_index].add_original_block(*le_block);
    delete le_block;

    // operators/upper_or_equal
    Block* ue_block = new Block();
    ue_block -> set_block_RGBA(2, 168, 21, 255);
    ue_block -> set_ghost_RGBA(59, 235, 76, 255);
    ue_block -> add_input();
    ue_block -> add_text(">=", font);
    ue_block -> add_input();

    ue_block -> block_id.general_type = OP;
    ue_block -> block_id.id_number = 15;
    all_original_managers[operators_index].add_original_block(*ue_block);
    delete ue_block;

    // operators/AND
    Block* and_block = new Block();
    and_block -> set_block_RGBA(2, 168, 21, 255);
    and_block -> set_ghost_RGBA(59, 235, 76, 255);
    and_block -> add_input();
    and_block -> add_text("&&", font);
    and_block -> add_input();

    and_block -> block_id.general_type = OP;
    and_block -> block_id.id_number = 16;
    all_original_managers[operators_index].add_original_block(*and_block);
    delete and_block;

    // operators/OR
    Block* or_block = new Block();
    or_block -> set_block_RGBA(2, 168, 21, 255);
    or_block -> set_ghost_RGBA(59, 235, 76, 255);
    or_block -> add_input();
    or_block -> add_text("||", font);
    or_block -> add_input();

    or_block -> block_id.general_type = OP;
    or_block -> block_id.id_number = 17;
    all_original_managers[operators_index].add_original_block(*or_block);
    delete or_block;

    // operators/NOT
    Block* not_block = new Block();
    not_block -> set_block_RGBA(2, 168, 21, 255);
    not_block -> set_ghost_RGBA(59, 235, 76, 255);
    not_block -> add_text("!", font);
    not_block -> add_input();

    not_block -> block_id.general_type = OP;
    not_block -> block_id.id_number = 18;
    all_original_managers[operators_index].add_original_block(*not_block);
    delete not_block;

    // operators/XOR
    Block* xor_block = new Block();
    xor_block -> set_block_RGBA(2, 168, 21, 255);
    xor_block -> set_ghost_RGBA(59, 235, 76, 255);
    xor_block -> add_input();
    xor_block -> add_text("^", font);
    xor_block -> add_input();

    xor_block -> block_id.general_type = OP;
    xor_block -> block_id.id_number = 19;
    all_original_managers[operators_index].add_original_block(*xor_block);
    delete xor_block;

    // operators/length
    Block* length_block = new Block();
    length_block -> set_block_RGBA(2, 168, 21, 255);
    length_block -> set_ghost_RGBA(59, 235, 76, 255);
    length_block -> add_text("length", font);
    length_block -> add_input();

    length_block -> block_id.general_type = OP;
    length_block -> block_id.id_number = 20;
    all_original_managers[operators_index].add_original_block(*length_block);
    delete length_block;

    // operators/Nth_char
    Block* nth_char_block = new Block();
    nth_char_block -> set_block_RGBA(2, 168, 21, 255);
    nth_char_block -> set_ghost_RGBA(59, 235, 76, 255);
    nth_char_block -> add_input();
    nth_char_block -> add_text("th character of", font);
    nth_char_block -> add_input();

    nth_char_block -> block_id.general_type = OP;
    nth_char_block -> block_id.id_number = 21;
    all_original_managers[operators_index].add_original_block(*nth_char_block);
    delete nth_char_block;

    // operators/merge_strings
    Block* merge_block = new Block();
    merge_block -> set_block_RGBA(2, 168, 21, 255);
    merge_block -> set_ghost_RGBA(59, 235, 76, 255);
    merge_block -> add_text("merge", font);
    merge_block -> add_input();
    merge_block -> add_text("and", font);
    merge_block -> add_input();

    merge_block -> block_id.general_type = OP;
    merge_block -> block_id.id_number = 22;
    all_original_managers[operators_index].add_original_block(*merge_block);
    delete merge_block;
}
