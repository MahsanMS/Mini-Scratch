#ifndef UI
#define UI
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfx.h>

struct TextBox
{
    Sint16 x, y, w, h;
    bool active = false;
    bool hover = false;

    vector<string> lines;
    string current_line;

    int cursor_counter = 0;

    // colors of textbox
    Uint8 box_r = 255, box_g = 255, box_b = 255, box_a = 255;
    Uint8 text_r = 255, text_g = 255, text_b = 255, text_a = 255;
    Uint8 active_r = 0, active_g = 255, active_b = 0, active_a = 255;
    Uint8 hover_r = 128, hover_g = 128, hover_b = 128, hover_a = 255;

    TextBox(Sint16 X, Sint16 Y, Sint16 W, Sint16 H)
    {
        x = X; y = Y; w = W; h = H;
    }

    void set_box_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        box_r = r; box_g = g; box_b = b; box_a = a;
    }

    void set_text_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        text_r = r; text_g = g; text_b = b; text_a = a;
    }

    void set_active_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        active_r = r; active_g = g; active_b = b; active_a = a;
    }

    void set_hover_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        hover_r = r; hover_g = g; hover_b = b; hover_a = a;
    }

    void manage(const SDL_Event &e)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            Sint16 mx = e.button.x;
            Sint16 my = e.button.y;
            active = x <= mx && mx <= x + w && y <= my && my <= y + h;
        }

        if (!active)
        {
            Sint16 mx = e.button.x;
            Sint16 my = e.button.y;
            hover = x <= mx && mx <= x + w && y <= my && my <= y + h;
            return;
        }

        if (e.type == SDL_TEXTINPUT)
            current_line += e.text.text;

        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (!current_line.empty())
                    current_line.pop_back();
                else if (!lines.empty())
                {
                    current_line = lines.back();
                    lines.pop_back();
                }
            }

            else if (e.key.keysym.sym == SDLK_RETURN)
            {
                lines.push_back(current_line);
                current_line.clear();
            }
        }
    }

    void render(SDL_Renderer *renderer)
    {
        if (active)
            rectangleRGBA(renderer, x, y, x + w, y + h, active_r, active_g, active_b, active_a);
        else if (hover)
            rectangleRGBA(renderer, x, y, x + w, y + h, hover_r, hover_g, hover_b, hover_a);
        else
            rectangleRGBA(renderer, x, y, x + w, y + h, box_r, box_g, box_b, box_a);

        const Sint16 text_x = x + 10;
        Sint16 text_y = y + 10;

        for (auto l : lines)
        {
            stringRGBA(renderer, text_x, text_y, l.c_str(), text_r, text_g, text_b, text_a);
            text_y += 20;
        }

        string temp = current_line;
        if (active && cursor_counter <= 25) temp += "|";

        stringRGBA(renderer, text_x, text_y, temp.c_str(), text_r, text_g, text_b, text_a);

        cursor_counter = (1 + cursor_counter) % 45;
    }
};

struct Button
{
    Sint16 x, y, w, h, radius;
    std::function<void()> callback;
    bool active = false;
    bool hover = false;

    Uint8 button_r = 255, button_g = 255, button_b = 255, button_a = 255;
    Uint8 active_r = 0, active_g = 255, active_b = 0, active_a = 255;
    Uint8 hover_r = 128, hover_g = 128, hover_b = 128, hover_a = 255;

    Button(Sint16 X, Sint16 Y, Sint16 W, Sint16 H, Sint16 rad)
    {
        x = X; y = Y; w = W; h = H; radius = rad;
    }

    void set_button_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        button_r = r; button_g = g; button_b = b; button_a = a;
    }

    void set_active_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        active_r = r; active_g = g; active_b = b; active_a = a;
    }

    void set_hover_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        hover_r = r; hover_g = g; hover_b = b; hover_a = a;
    }

    void manage_event(const SDL_Event &e)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            Sint16 mx = e.button.x;
            Sint16 my = e.button.y;
            active = x <= mx && mx <= x + w && y <= my && my <= y + h;
            if (active)
                callback();
        }
        else
        {
            Sint16 mx = e.button.x;
            Sint16 my = e.button.y;
            hover = x <= mx && mx <= x + w && y <= my && my <= y + h;
            active = false;
        }
    }

    void render_button(SDL_Renderer *renderer)
    {
        if (active)
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, active_r, active_g, active_b, active_a);
        else if (hover)
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, hover_r, hover_g, hover_b, hover_a);
        else
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, button_r, button_g, button_b, button_a);
    }
};

#endif