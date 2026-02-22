#ifndef MINI_SCRATCH_CUSTOM_MENU_H
#define MINI_SCRATCH_CUSTOM_MENU_H

#include "UI.h"

int SCREEN_HEIGHT;

bool pencil = true;
bool draw = false;
bool erasesel = false;
bool erasing = false;

bool drag_r = false;
bool drag_g = false;
bool drag_b = false;

//color rectangle
struct handle {
    int y;
    int start;
    int end;
    int handle_x;
    int handle_r;
};

//shapes
enum place{ PALLETE, AREA };

struct shape{
    place place;
    SDL_Texture* tex;
    SDL_Rect rectshape;
};

struct CustomMenuState {

    SDL_Rect penbtn = {10, 10, 20, 20};
    SDL_Rect erasepenbtn;

    int pensize = 20;
    int erasesize = 20;

    SDL_Rect middle_sprite;

    std::vector<shape> shapes;
    std::vector<shape> new_shapes;

    SDL_Texture* pen = nullptr;
    SDL_Texture* eraser = nullptr;

    SDL_Texture* Ri = nullptr;
    SDL_Texture* Gi = nullptr;
    SDL_Texture* Bi = nullptr;

    SDL_Texture* erase = nullptr;

    SDL_Rect R = {10, 40, 90, 30};
    SDL_Rect G = {10, 70, 90, 30};
    SDL_Rect B = {10, 110, 90, 30};

    SDL_Rect erasebtn;

    handle red = {40, 10, 100, 10, 7};
    handle green {70, 10, 100, 10, 7};
    handle blue = {110, 10, 100, 10, 7};

    int mx = 0;
    int my = 0;

    int offsetx = 0;
    int offsety = 0;

    bool dragging = false;
    int select = -1;

    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
};

// function declarations
void custom_manage_event(Sprite& s, SDL_Renderer* renderer, SDL_Event& event, CustomMenuState& state) {
    int w,h;
    SDL_GetRendererOutputSize(renderer,&w,&h);

    SDL_GetMouseState(&state.mx,&state.my);

    SDL_Rect area = {
        int(0.40 * w),
        int(0.15 * h),
        int(0.45 * w),
        int(0.70 * h)
    };

    int mid_w = int(0.8 * area.w);
    int mid_h = int(0.8 * area.h);

    state.middle_sprite = {
        area.x + (area.w - mid_w)/2,
        area.y + (area.h - mid_h)/2,
        mid_w,
        mid_h
    };

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        for(int i = state.shapes.size()-1 ; i>=0 ; i--)
        {
            SDL_Rect r = state.shapes[i].rectshape;

            if(state.mx>=r.x && state.mx<=r.x+r.w &&
               state.my>=r.y && state.my<=r.y+r.h)
            {
                if(state.shapes[i].place == PALLETE)
                {
                    shape copy = state.shapes[i];
                    copy.place = AREA;

                    state.new_shapes.push_back(copy);
                    state.select = state.new_shapes.size()-1;
                }

                state.dragging = true;
                state.offsetx = state.mx - r.x;
                state.offsety = state.my - r.y;
                break;
            }
        }

        if (pencil){
            draw = true;
        }

        if (erasesel){
            erasing = true;
        }
    }

    if (event.type == SDL_MOUSEMOTION)
    {
        if (state.dragging && state.select!=-1)
        {
            state.new_shapes[state.select].rectshape.x =
                    state.mx - state.offsetx;

            state.new_shapes[state.select].rectshape.y =
                    state.my - state.offsety;
        }

        if (drag_r){
            state.red.handle_x =
                std::max(state.red.start,
                std::min(state.mx,state.red.end));

            float t = float(state.red.handle_x-state.red.start)/
                     float(state.red.end-state.red.start);

            state.r = Uint8(255*t);
        }

        if (drag_g){
            state.green.handle_x =
                std::max(state.green.start,
                std::min(state.mx,state.green.end));

            float t = float(state.green.handle_x-state.green.start)/
                     float(state.green.end-state.green.start);

            state.g = Uint8(255*t);
        }

        if (drag_b){
            state.blue.handle_x =
                std::max(state.blue.start,
                std::min(state.mx,state.blue.end));

            float t = float(state.blue.handle_x-state.blue.start)/
                     float(state.blue.end-state.blue.start);

            state.b = Uint8(255*t);
        }
    }



    if (event.type == SDL_MOUSEBUTTONUP)
    {
        draw=false;
        erasing=false;
        state.dragging=false;
        state.select=-1;
    }


    if (event.type == SDL_MOUSEWHEEL)
    {
        if (pencil){
            if (event.wheel.y>0) state.pensize+=2;
            else state.pensize-=2;

            if (state.pensize<5) state.pensize=5;
            if (state.pensize>50) state.pensize=50;
        }
        else if (erasesel){
            if (event.wheel.y>0) state.erasesize+=2;
            else state.erasesize-=2;

            if (state.erasesize<5) state.erasesize=5;
            if (state.erasesize>50) state.erasesize=50;
        }
    }
}

void render_menu(Sprite& s, SDL_Renderer* renderer, CustomMenuState& state) {

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, s.customs[s.current_custom].texture, NULL, &state.middle_sprite);

    SDL_RenderCopy(renderer, s.customs[s.current_custom].canvas, NULL, &state.middle_sprite);

    for(auto &b : state.shapes)
        SDL_RenderCopy(renderer,b.tex,NULL,&b.rectshape);

    for(auto &b : state.new_shapes){
        SDL_SetRenderTarget(renderer,
            s.customs[s.current_custom].canvas);

        SDL_RenderCopy(renderer,b.tex,NULL,&b.rectshape);
        SDL_SetRenderTarget(renderer,NULL);
    }

    if(state.dragging && state.select!=-1)
    {
        state.new_shapes[state.select].rectshape.x =
                state.mx - state.offsetx;

        state.new_shapes[state.select].rectshape.y =
                state.my - state.offsety;
    }

    state.penbtn.w = state.pensize;
    state.penbtn.h = state.pensize;

    state.erasepenbtn.w = state.erasesize;
    state.erasepenbtn.h = state.erasesize;

    SDL_SetTextureColorMod(state.pen, state.r, state.g, state.b);

    SDL_RenderCopy(renderer,state.pen,NULL,&state.penbtn);
    SDL_RenderCopy(renderer,state.eraser,NULL,&state.erasepenbtn);

    filledCircleRGBA(renderer, state.red.handle_x, state.red.y, state.red.handle_r, 255,255,255,255);

    filledCircleRGBA(renderer, state.green.handle_x, state.green.y, state.green.handle_r, 255,255,255,255);

    filledCircleRGBA(renderer, state.blue.handle_x, state.blue.y, state.blue.handle_r, 255,255,255,255);

    SDL_RenderPresent(renderer);
}

#endif