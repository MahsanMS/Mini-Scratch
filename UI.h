#ifndef MINI_SCRATCH_UI_H
#define MINI_SCRATCH_UI_H

using namespace std;

SDL_DisplayMode DM;
int count;

bool change_sprite = false;
bool change_custom = false;

struct TextItem {
    string text;
    int w, h;
};

struct InputBox
{
    Sint16 x, y;
    Sint16 rel_x, rel_y, w, h;
    bool active = false;
    bool hover = false;

    TextItem line;

    int cursor_counter = 0;

    // colors of inputbox
    Uint8 box_r = 255, box_g = 255, box_b = 255, box_a = 255;
    Uint8 text_r = 255, text_g = 255, text_b = 255, text_a = 255;
    Uint8 active_r = 0, active_g = 255, active_b = 0, active_a = 255;
    Uint8 hover_r = 128, hover_g = 128, hover_b = 128, hover_a = 255;

    InputBox()
    {
        w = 10, h = 18;
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

    bool manage_event(const SDL_Event &e)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            Sint16 mx = e.button.x;
            Sint16 my = e.button.y;
            active = x <= mx && mx <= x + w && y <= my && my <= y + h;
        }

        if (e.type == SDL_MOUSEMOTION)
        {
            Sint16 mx = e.motion.x;
            Sint16 my = e.motion.y;
            hover = x <= mx && mx <= x + w && y <= my && my <= y + h;
        }

        if (hover) return true;
        if (!active) return false;

        if (e.type == SDL_TEXTINPUT)
            line.text += e.text.text;

        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (!line.text.empty())
                {
                    line.text.pop_back();
                }
            }
        }

        return true;
    }

    void render(SDL_Renderer *renderer, TTF_Font *font)
    {
        if (active)
            rectangleRGBA(renderer, x, y, x + w, y + h, active_r, active_g, active_b, active_a);
        else if (hover)
            rectangleRGBA(renderer, x, y, x + w, y + h, hover_r, hover_g, hover_b, hover_a);
        else
            rectangleRGBA(renderer, x, y, x + w, y + h, box_r, box_g, box_b, box_a);

        cursor_counter = (cursor_counter + 1) % 45;

        TTF_SizeUTF8(font, line.text.c_str(), &line.w, &line.h);

        w = line.w + 10;

        if (line.text == "" && active && cursor_counter <= 25)
        {
            SDL_Rect cursor = {x + 5, y + 3, 2, line.h - 5};
            SDL_SetRenderDrawColor(renderer, text_r, text_g, text_b, text_a);

            SDL_RenderFillRect(renderer, &cursor);
        }

        else
        {
            SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font, line.text.c_str(), SDL_Color{text_r, text_g, text_b,
                text_a});

            if (!text_surface) return;

            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

            SDL_Rect text_dst = {x + 4, y, text_surface -> w, text_surface -> h};
            SDL_RenderCopy(renderer, text_texture, nullptr, &text_dst);

            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);

            if (active && cursor_counter <= 25)
            {
                SDL_Rect cursor = {x + w - 5, y + 3, 2, line.h - 5};
                SDL_SetRenderDrawColor(renderer, text_r, text_g, text_b, text_a);

                SDL_RenderFillRect(renderer, &cursor);
            }
        }
    }
};

struct Button
{
    Sint16 x, y, w, h, radius;
    std::function<void()> callback;
    bool active = false;
    bool hover = false;

    Uint8 button_r = 255, button_g = 255, button_b = 255, button_a = 255;
    Uint8 active_r = 64, active_g = 64, active_b = 64, active_a = 255;
    Uint8 hover_r = 128, hover_g = 128, hover_b = 128, hover_a = 255;

    SDL_Texture* icon = nullptr;

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

    bool manage_event(const SDL_Event &e)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            Sint16 mx = e.button.x;
            Sint16 my = e.button.y;
            active = x <= mx && mx <= x + w && y <= my && my <= y + h;
            if (active)
            {
                callback();
                return true;
            }
        }

        else if (e.type == SDL_MOUSEMOTION)
        {
            Sint16 mx = e.motion.x;
            Sint16 my = e.motion.y;
            hover = x <= mx && mx <= x + w && y <= my && my <= y + h;
            active = false;
        }

        return false;
    }

    void render(SDL_Renderer *renderer)
    {
        if (active)
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, active_r, active_g, active_b, active_a);
        else if (hover)
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, hover_r, hover_g, hover_b, hover_a);
        else
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, button_r, button_g, button_b, button_a);

        if (icon)
        {
            SDL_Rect rect = {x, y, w, h};
            SDL_RenderCopy(renderer, icon, nullptr, &rect);
        }
    }
};

enum general_type {
    MOTION, LOOKS, SOUND, EVENT, CONT, SENSE, OP, VAR, FUNC
};

enum control_blocks
{
    IF, ENDIF, IFELSE, ELSE, ENDELSE, REPEAT, ENDREPEAT
};

struct id {
    general_type general_type;
    int id_number;
    control_blocks control_mode;
};

struct Block
{
    id block_id;
    bool parent_id = true;

    Sint16 x, y;
    Sint16 ghost_x, ghost_y;
    int width, height;
    int offset_x, offset_y;
    bool dragging = false;

    bool is_original = false;
    bool new_child = false;

    bool child_change_position = false;

    string look;
    // 1 -> text
    // 2 -> input

    Uint8 block_r = 255, block_g = 255, block_b = 255, block_a = 255;
    Uint8 ghost_r = 128, ghost_g = 128, ghost_b = 128, ghost_a = 255;
    Uint8 text_r = 0, text_g = 0, text_b = 0, text_a = 255;

    vector<TextItem> texts;
    vector<InputBox> inputs;

    Block()
    {
        x = 0; y = 0; height = 20; width = 10;
    }

    void set_block_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        block_r = r; block_g = g; block_b = b; block_a = a;
    }

    void set_ghost_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        ghost_r = r; ghost_g = g; ghost_b = b; ghost_a = a;
    }

    void set_text_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        text_r = r; text_g = g; text_b = b; text_a = a;
    }

    void set_inputs_box_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        for (auto& inp: inputs)
            inp.set_box_RGBA(r, g, b, a);
    }

    void set_inputs_text_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        for (auto& inp: inputs)
            inp.set_text_RGBA(r, g, b, a);
    }

    void set_inputs_active_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        for (auto& inp: inputs)
            inp.set_active_RGBA(r, g, b, a);
    }

    void set_inputs_hover_RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        for (auto& inp: inputs)
            inp.set_hover_RGBA(r, g, b, a);
    }

    void add_text(string t, TTF_Font* font)
    {
        TextItem item;
        item.text = t;
        TTF_SizeUTF8(font, t.c_str(), &item.w, &item.h);

        texts.push_back(item);

        width += item.w;
        width += 5;
        height = max(height, item.h + 10);

        look += '1';
    }

    void add_input()
    {
        InputBox inp_box;
        inp_box.rel_x = width;
        inp_box.rel_y = 5;
        inp_box.h = max(height - 10, 18);

        inputs.push_back(inp_box);

        width += inp_box.w;
        width += 5;

        look += '2';
    }

    void manage_event(const SDL_Event& e)
    {
        bool new_input = false;
        for (auto& it: inputs)
            new_input |= it.manage_event(e);

        if (new_input) return;

        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int mx = e.button.x;
            int my = e.button.y;

            ghost_x = x;
            ghost_y = y;

            if (x <= mx && mx <= x + width && y <= my && my <= y + height)
            {
                dragging = true;
                offset_x = mx - ghost_x;
                offset_y = my - ghost_y;
            }
        }

        if (e.type == SDL_MOUSEMOTION && dragging)
        {
            ghost_x = e.motion.x - offset_x;
            ghost_y = e.motion.y - offset_y;
        }

        if (e.type == SDL_MOUSEBUTTONUP && dragging)
        {
            if (is_original)
            {
                new_child = true;
            }

            else if (dragging)
            {
                child_change_position = true;
            }

            dragging = false;
        }
    }

    void render(SDL_Renderer* renderer, TTF_Font* font)
    {
        boxRGBA(renderer, x, y, x + width, y + height, block_r, block_g, block_b, block_a);

        int x2 = x + 5;
        int text_counter = 0;
        int input_counter = 0;
        int new_width = 5;

        for (char ch: look)
        {
            if (ch == '1')
            {
                TextItem &t = texts[text_counter++];
                SDL_Color color = {text_r, text_g, text_b, text_a};

                SDL_Surface* s = TTF_RenderUTF8_Blended(font, t.text.c_str(), color);

                SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, s);

                SDL_Rect dst = { x2, y + 5, s->w, s->h };
                SDL_RenderCopy(renderer, tex, nullptr, &dst);

                x2 += t.w + 5;

                SDL_FreeSurface(s);
                SDL_DestroyTexture(tex);

                new_width += t.w + 5;
            }

            else if (ch == '2')
            {
                InputBox& inp = inputs[input_counter++];

                inp.x = x2;
                inp.y = y + inp.rel_y;

                inp.render(renderer, font);

                new_width += inp.w + 5;
                x2 += inp.w + 5;
            }
        }

        width = new_width + 5;

        if (dragging)
        {
            boxRGBA(renderer, ghost_x, ghost_y, ghost_x + width, ghost_y + height, ghost_r, ghost_g,
                ghost_b, ghost_a);
        }
    }
};

struct BlockManager
{
    Sint16 x, y;
    int height, width;
    int block_height = 20;

    int max_blocks_to_show;
    int start_block = 0;
    int end_block = 1;

    Uint8 border_r = 255, border_g = 255, border_b = 255, border_a = 255;

    vector<Block> blocks;

    BlockManager(Sint16 _x, Sint16 _y, int w, int h, int max_show)
    {
        x = _x; y = _y; width = w; height = h; max_blocks_to_show = max_show;
    }

    void set_blocks_position()
    {
        for (int i = start_block; i < end_block; i++)
        {
            blocks[i].x = x + 10;
            blocks[i].y = y + (i - start_block) * 35 + 7;
        }
    }

    void go_down()
    {
        if (end_block < blocks.size())
        {
            start_block++;
            end_block++;

            set_blocks_position();
        }
    }

    void go_up()
    {
        if (start_block > 0)
        {
            start_block--;
            end_block--;

            set_blocks_position();
        }
    }

    void handle_original(Block& original_block, TTF_Font* font)
    {
        if (blocks.empty() && original_block.block_id.general_type != EVENT) return;
        if (!blocks.empty() && original_block.block_id.general_type == EVENT) return;

        if (original_block.new_child)
        {
            original_block.new_child = false;

            int center_x = original_block.ghost_x + original_block.width / 2;
            int center_y = original_block.ghost_y + original_block.height / 2;

            if (x < center_x && center_x < x + width && y < center_y && center_y < y + height)
            {
                if (original_block.block_id.general_type == CONT)
                {
                    switch (original_block.block_id.id_number)
                    {
                    case 0:
                        {
                            Block start_if = original_block;
                            Block end_if;

                            start_if.is_original = true;  // to not move
                            end_if.is_original = true;  // to not move

                            start_if.x = x + 10;
                            start_if.y = y + blocks.size() * 35 + 7;

                            start_if.block_id.control_mode = IF;
                            start_if.add_input();
                            blocks.push_back(start_if);

                            end_if.add_text("endif", font);

                            end_if.set_block_RGBA(original_block.block_r, original_block.block_g, original_block.block_b, original_block.block_a);
                            end_if.set_ghost_RGBA(original_block.ghost_r, original_block.ghost_g, original_block.ghost_b, original_block.ghost_a);

                            end_if.x = x + 10;
                            end_if.y = y + blocks.size() * 35 + 7;

                            end_if.block_id = original_block.block_id;
                            end_if.parent_id = original_block.parent_id;
                            end_if.block_id.control_mode = ENDIF;
                            blocks.push_back(end_if);
                            break;
                        }

                    case 1:
                        {
                            Block start_if;
                            start_if.is_original = true; // to not move

                            start_if.set_block_RGBA(original_block.block_r, original_block.block_g, original_block.block_b, original_block.block_a);
                            start_if.set_ghost_RGBA(original_block.ghost_r, original_block.ghost_g, original_block.ghost_b, original_block.ghost_a);

                            start_if.block_id = original_block.block_id;
                            start_if.parent_id = original_block.parent_id;

                            Block start_else = start_if, endelse = start_if;

                            start_if.x = x + 10;
                            start_if.y = y + blocks.size() * 35 + 7;
                            start_if.add_text("if", font);
                            start_if.block_id.control_mode = IFELSE;
                            start_if.add_input();
                            blocks.push_back(start_if);

                            start_else.x = x + 10;
                            start_else.y = y + blocks.size() * 35 + 7;
                            start_else.add_text("else", font);
                            start_else.block_id.control_mode = ELSE;
                            blocks.push_back(start_else);

                            endelse.x = x + 10;
                            endelse.y = y + blocks.size() * 35 + 7;
                            endelse.add_text("endelse", font);
                            endelse.block_id.control_mode = ENDELSE;
                            blocks.push_back(endelse);

                            break;
                        }

                    case 2:
                        {
                            Block start_repeat = original_block;
                            Block end_repeat;

                            start_repeat.is_original = true;
                            end_repeat.is_original = true;

                            start_repeat.x = x + 10;
                            start_repeat.y = y + blocks.size() * 35 + 7;

                            start_repeat.block_id.control_mode = REPEAT;
                            blocks.push_back(start_repeat);

                            end_repeat.add_text("endrepeat", font);
                            end_repeat.set_block_RGBA(original_block.block_r, original_block.block_g, original_block.block_b, original_block.block_a);
                            end_repeat.set_ghost_RGBA(original_block.ghost_r, original_block.ghost_g, original_block.ghost_b, original_block.ghost_a);

                            end_repeat.x = x + 10;
                            end_repeat.y = y + blocks.size() * 35 + 7;

                            end_repeat.block_id.general_type = CONT;
                            end_repeat.parent_id = original_block.parent_id;
                            end_repeat.block_id.control_mode = ENDREPEAT;
                            blocks.push_back(end_repeat);

                            break;
                        }
                    }
                }

                else
                {
                    Block new_block = original_block;
                    new_block.is_original = original_block.block_id.general_type == EVENT;

                    new_block.x = x + 10;
                    new_block.y = y + blocks.size() * 35 + 7;

                    blocks.push_back(new_block);
                }

                end_block = min((int)blocks.size(), start_block + max_blocks_to_show);
            }
        }
    }

    void manage_event(SDL_Event& e)
    {
        if (blocks.empty()) return;
        for (int i = start_block; i < end_block; i++)
        {
            Block& it = blocks[i];
            it.manage_event(e);

            if (it.child_change_position)
            {
                it.child_change_position = false;

                if ((it.ghost_y - y) / 35 != (it.y - y) / 35)
                {
                    int index_to_move = (it.ghost_y - y) / 35;

                    if (index_to_move <= 0) index_to_move = 0;
                    else if (index_to_move > blocks.size() - 1) index_to_move = blocks.size() - 1;

                    if (start_block == 0 && index_to_move == 0) index_to_move = 1;

                    Block copy = blocks[i];
                    blocks.erase(blocks.begin() + i);
                    blocks.insert(blocks.begin() + start_block + index_to_move, copy);

                    for (int j = 0; j < blocks.size(); j++)
                    {
                        blocks[start_block + j].y = y + j * 35 + 7;
                    }

                    break;
                }
            }
        }
    }

    void render(SDL_Renderer *renderer, TTF_Font* font)
    {
        rectangleRGBA(renderer, x, y, x + width, y + height, border_r, border_g, border_b, border_a);

        if (!blocks.empty())
        {
            for (int i = start_block; i < end_block; i++)
            {
                blocks[i].render(renderer, font);
            }
        }
    }
};

struct OriginalBlocksManager
{
    Sint16 x, y;
    int height, width;

    int max_blocks_to_show;
    int start_block = 0;
    int end_block = 1;

    Uint8 border_r = 255, border_g = 255, border_b = 255, border_a = 255;

    vector<Block> original_blocks;

    OriginalBlocksManager() {}

    OriginalBlocksManager(Sint16 _x, Sint16 _y, int w, int h, int max_show)
    {
        x = _x; y = _y; width = w; height = h; max_blocks_to_show = max_show;
    }

    void add_original_block(Block &block)
    {
        original_blocks.push_back(block);
        original_blocks.back().x = x + 10;
        original_blocks.back().y = y + (original_blocks.size() - 1) * 35 + 7;
        original_blocks.back().is_original = true;

        end_block = min((int)original_blocks.size(), max_blocks_to_show);
    }

    void set_blocks_position()
    {
        for (int i = start_block; i < end_block; i++)
        {
            original_blocks[i].x = x + 10;
            original_blocks[i].y = y + (i - start_block) * 35 + 7;
        }
    }

    void go_down()
    {
        if (end_block < original_blocks.size())
        {
            start_block++;
            end_block++;

            set_blocks_position();
        }
    }

    void go_up()
    {
        if (start_block > 0)
        {
            start_block--;
            end_block--;

            set_blocks_position();
        }
    }

    void manage_event(SDL_Event& e, BlockManager& manager, TTF_Font* font)
    {
        if (original_blocks.empty()) return;
        for (int i = start_block; i < end_block; i++)
        {
            auto& it = original_blocks[i];
            it.manage_event(e);
            manager.handle_original(it, font);
        }
    }

    void render(SDL_Renderer* renderer, TTF_Font* font)
    {
        rectangleRGBA(renderer, x, y, x + width, y + height, border_r, border_g, border_b, border_a);
        if (!original_blocks.empty())
        {
            for (int i = start_block; i < end_block; i++)
            {
                original_blocks[i].render(renderer, font);
            }
        }
    }
};

struct sprite_state {
    int x,y;
    float w,h;
    int direction;
    float minX, maxX, minY, maxY;
    int size;
    bool visible;
    sprite_state() {
        x = 0.0f;
        y = 0.0f;
        direction = 0.0f;      // Facing right
        visible = true;
        size=100.0f;

        // Scratch screen dimensions
        minX = -240.0f;
        maxX = 240.0f;
        minY = -180.0f;
        maxY = 180.0f;
    }
};

struct Custom {
    string name;
    SDL_Texture* texture;
    SDL_Texture* canvas;
};

struct CustomSelection
{
    Custom* custom;
    bool active = false;
    bool new_activate_action = false;

    Button select_button;

    int thumb_size = 48;
    int item_height = 64;

    CustomSelection(Custom* cus, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
        : custom(cus), select_button(x, y, w, h, 6)
    {
        select_button.callback = [&]()
        {
            active = true;
            new_activate_action = true;
        };
    }

    bool manage_event(SDL_Event& e)
    {
        new_activate_action = select_button.manage_event(e);
        if (new_activate_action)
            change_custom = true;
        return new_activate_action;
    }

    void render(SDL_Renderer* renderer, TTF_Font* font)
    {
        if (!active)
        {
            select_button.set_button_RGBA(255, 255, 255, 255);
            select_button.set_hover_RGBA(128, 128, 128, 255);
            select_button.set_active_RGBA(64, 64, 64, 255);
        }
        else
        {
            select_button.set_button_RGBA(120, 200, 120, 255);
            select_button.set_hover_RGBA(160, 220, 160, 255);
            select_button.set_active_RGBA(60, 160, 60, 255);
        }

        select_button.render(renderer);

        if (!custom) return;

        // thumbnail
        SDL_Texture* tex = custom->canvas ? custom->canvas : custom->texture;
        if (tex)
        {
            SDL_Rect thumb;
            thumb.x = select_button.x + 6;
            thumb.y = select_button.y + (select_button.h - thumb_size) / 2;
            thumb.w = thumb_size;
            thumb.h = thumb_size;

            SDL_RenderCopy(renderer, tex, nullptr, &thumb);
        }

        // name
        SDL_Color color = {0, 0, 0, 255};

        SDL_Surface* s = TTF_RenderUTF8_Blended(font, custom -> name.c_str(), color);
        if (!s) return;

        SDL_Texture* name_tex = SDL_CreateTextureFromSurface(renderer, s);

        SDL_Rect name_dst;
        name_dst.x = select_button.x + thumb_size + 14;
        name_dst.y = select_button.y + (select_button.h - s -> h) / 2;
        name_dst.w = s -> w;
        name_dst.h = s -> h;

        SDL_RenderCopy(renderer, name_tex, nullptr, &name_dst);

        SDL_FreeSurface(s);
        SDL_DestroyTexture(name_tex);
    }
};

struct CustomManager
{
    Sint16 x, y;
    int width, height;

    int max_customs_to_show;
    int start_custom = 0;
    int end_custom = 1;

    int index_of_active = 0;

    int item_height = 62;
    int gap = 7;

    vector<CustomSelection> customs;

    Uint8 border_r = 255, border_g = 255, border_b = 255, border_a = 255;

    CustomManager() {}

    CustomManager(Sint16 _x, Sint16 _y, int w, int h, int max_show)
    {
        x = _x;
        y = _y;
        width = w;
        height = h;
        max_customs_to_show = max_show;
    }

    void set_customs_position()
    {
        for (int i = start_custom; i < end_custom; i++)
        {
            customs[i].select_button.x = x + 10;
            customs[i].select_button.y = y + (i - start_custom) * (item_height + gap) + 10;
            customs[i].select_button.h = item_height;
            customs[i].select_button.w = width - 38;
        }
    }

    void go_down()
    {
        if (end_custom < customs.size())
        {
            start_custom++;
            end_custom++;
            set_customs_position();
        }
    }

    void go_up()
    {
        if (start_custom > 0)
        {
            start_custom--;
            end_custom--;
            set_customs_position();
        }
    }

    void add_custom(Custom* custom)
    {
        CustomSelection sel(custom, x + 10, y + customs.size() * (item_height + gap) + 10,
                            width - 38, item_height);

        for (auto& c : customs)
            c.active = false;

        sel.active = true;

        customs.push_back(sel);

        end_custom = min((int)customs.size(), start_custom + max_customs_to_show);
        set_customs_position();

        index_of_active = customs.size() - 1;
    }

    void manage_event(SDL_Event& e)
    {
        for (int i = start_custom; i < end_custom; i++)
        {
            auto& it = customs[i];
            it.manage_event(e);

            if (it.new_activate_action)
            {
                for (auto& other : customs)
                    other.active = false;

                it.active = true;
                it.new_activate_action = false;

                index_of_active = i;
                break;
            }
        }
    }

    void render(SDL_Renderer* renderer, TTF_Font* font)
    {
        rectangleRGBA(renderer, x, y, x + width, y + height,
                      border_r, border_g, border_b, border_a);

        for (int i = start_custom; i < end_custom; i++)
        {
            customs[i].render(renderer, font);
        }
    }
};

struct BackDrop {
    string name;
    float width,height;
    SDL_Texture* texture;
};

struct Stage {
    std::vector<BackDrop> backdrops;
    int current_backdrop = 0;
};

struct Sprite {
    std::string name;
    sprite_state state;
    std::unordered_map<string,float> var;

    BlockManager blocks;
    int current_block;
    bool is_running = false;
    Custom customs[15];
    int current_custom = 0;
    int scaled_w = 0;
    int scaled_h = 0;
    SDL_Rect rect;
    std::string saytext;
    int say_time=0;
    std::string thinktext;
    int think_time=0;
    bool sprite_clicked = false;
    bool dragging = false;
    int offset_x=0;
    int offset_y=0;

    bool show = true;

    CustomManager custom_manager;

    Sprite() : blocks(0.239 * DM.w, 0.053 * DM.h, 0.425 * DM.w, 0.83 * DM.h, ::count)
    {}

    void manage_event(SDL_Event& e) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mx = e.button.x;
            int my = e.button.y;

            if (!dragging) {
                if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {
                    dragging=true;

                    offset_x = mx - rect.x;
                    offset_y = my - rect.y;
                    sprite_clicked = true;
                }
            }
        }

        if (e.type == SDL_MOUSEBUTTONUP && dragging) {
            dragging = false;
        }

        if (e.type == SDL_MOUSEMOTION && dragging)
        {
            state.x = e.motion.x - offset_x;
            state.y = e.motion.y - offset_y;
        }
    }
};

void render_speech(SDL_Renderer* renderer, Sprite& sprite) {
    //render bubble
    //render say text
}

void render_think(SDL_Renderer* renderer, Sprite& sprite) {
    //render bubble
    //render say text
}

void render_sprite(SDL_Renderer* renderer, Sprite& sprite)
{
    SDL_Point center;
    center.x = sprite.state.w/2;
    center.y = sprite.state.h/2;
    SDL_Texture* texture=sprite.customs[sprite.current_custom].texture;
    SDL_Texture* canva=sprite.customs[sprite.current_custom].canvas;

    SDL_Rect rect = {(int)(sprite.state.x * sprite.state.size / 100 - center.x * sprite.state.size / 100 + 0.8185 * DM.w), (int)(-sprite.state.y * sprite.state.size / 100 - center.y * sprite.state.size / 100 + 0.253 * DM.h), (int)sprite.state.w * sprite.state.size / 100, (int)sprite.state.h * sprite.state.size / 100};
    if (sprite.say_time !=0)
    {
        //render_speech(SDL_Renderer* renderer, Sprite& sprite)
    }

    if (sprite.say_time !=0)
    {
        // render_think(SDL_Renderer* renderer, Sprite& sprite)
    }

    SDL_RenderCopyEx(renderer,texture,NULL,&rect,sprite.state.direction,&center,SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer,canva,NULL,&rect,sprite.state.direction,&center,SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}

struct SpriteSelection
{
    Sprite* sprite;
    bool active = false;
    bool new_activate_action = false;

    Button select_button;

    SpriteSelection(Sprite* spr, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
        : sprite(spr), select_button(x, y, w, h, 6)
    {
        select_button.callback = [&]()
        {
            active = true;
            new_activate_action = true;
        };
    }

    bool manage_event(SDL_Event& e)
    {
        new_activate_action = select_button.manage_event(e);
        if (new_activate_action)
        {
            change_sprite = true;
        }
        return new_activate_action;
    }

    void render(SDL_Renderer* renderer, TTF_Font* font)
    {
        if (!active)
        {
            select_button.set_button_RGBA(255, 255, 255, 255);
            select_button.set_hover_RGBA(128, 128, 128, 255);
            select_button.set_active_RGBA(64, 64, 64, 255);
        }
        else
        {
            select_button.set_button_RGBA(66, 135, 245, 255);
            select_button.set_hover_RGBA(142, 182, 245, 255);
            select_button.set_active_RGBA(0, 61, 158, 255);
        }

        select_button.render(renderer);

        if (!sprite) return;

        SDL_Color color = {0, 0, 0, 255};

        SDL_Surface* s = TTF_RenderUTF8_Blended(font, sprite -> name.c_str(), color);
        if (!s) return;

        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, s);

        SDL_Rect dst;
        dst.x = select_button.x + 5;
        dst.y = select_button.y + 5;
        dst.w = s -> w;
        dst.h = s -> h;

        SDL_RenderCopy(renderer, tex, nullptr, &dst);

        SDL_FreeSurface(s);
        SDL_DestroyTexture(tex);
    }
};

struct SpriteManager
{
    Sint16 x, y;
    int width, height;

    int max_sprites_to_show;
    int start_sprite = 0;
    int end_sprite = 1;

    int index_of_active = 0;

    vector<SpriteSelection> sprites;

    Uint8 border_r = 255, border_g = 255, border_b = 255, border_a = 255;

    SpriteManager() {}

    SpriteManager(Sint16 _x, Sint16 _y, int w, int h, int max_show)
    {
        x = _x;
        y = _y;
        width = w;
        height = h;
        max_sprites_to_show = max_show;
    }

    void set_sprites_position()
    {
        for (int i = start_sprite; i < end_sprite; i++)
        {
            sprites[i].select_button.x = x + 10;
            sprites[i].select_button.y = y + (i - start_sprite) * 37 + 10;
        }
    }

    void go_down()
    {
        if (end_sprite < sprites.size())
        {
            start_sprite++;
            end_sprite++;
            set_sprites_position();
        }
    }

    void go_up()
    {
        if (start_sprite > 0)
        {
            start_sprite--;
            end_sprite--;
            set_sprites_position();
        }
    }

    void add_sprite(Sprite* sprite)
    {
        SpriteSelection sel(sprite, x + 10, y + sprites.size() * 37 + 10, width - 38, 28);

        for (auto& s : sprites)
            s.active = false;

        sel.active = true;

        sprites.push_back(sel);

        end_sprite = min((int)sprites.size(), start_sprite + max_sprites_to_show);
        set_sprites_position();

        index_of_active = sprites.size() - 1;
    }

    void manage_event(SDL_Event& e)
    {
        for (int i = start_sprite; i < end_sprite; i++)
        {
            auto& it = sprites[i];
            it.manage_event(e);

            if (it.new_activate_action)
            {
                for (auto& other : sprites)
                    other.active = false;

                it.active = true;
                it.new_activate_action = false;

                index_of_active = i;

                break;
            }
        }
    }

    void render(SDL_Renderer* renderer, TTF_Font* font)
    {
        rectangleRGBA(renderer, x, y, x + width, y + height, border_r, border_g, border_b, border_a);

        for (int i = start_sprite; i < end_sprite; i++)
        {
            sprites[i].render(renderer, font);
        }
    }
};

#endif