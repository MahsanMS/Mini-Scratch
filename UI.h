#ifndef UI
#define UI

using namespace std;

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
        w = 10, h = 27;
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

        else if (e.type == SDL_MOUSEMOTION)
        {
            Sint16 mx = e.motion.x;
            Sint16 my = e.motion.y;
            hover = x <= mx && mx <= x + w && y <= my && my <= y + h;
            active = false;
        }
    }

    void render(SDL_Renderer *renderer)
    {
        if (active)
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, active_r, active_g, active_b, active_a);
        else if (hover)
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, hover_r, hover_g, hover_b, hover_a);
        else
            roundedBoxRGBA(renderer, x, y, x + w, y + h, radius, button_r, button_g, button_b, button_a);
    }
};

struct Block
{
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

    BlockManager(Sint16 _x, Sint16 _y, int w, int h, int count)
    {
        x = _x; y = _y; width = w; height = h; max_blocks_to_show = count;
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

    void handle_original(Block& original_block)
    {
        if (original_block.new_child)
        {
            original_block.new_child = false;

            int center_x = original_block.ghost_x + original_block.width / 2;
            int center_y = original_block.ghost_y + original_block.height / 2;

            if (x < center_x && center_x < x + width && y < center_y && center_y < y + height)
            {
                Block new_block = original_block;
                new_block.is_original = false;

                new_block.x = x + 10;
                new_block.y = y + blocks.size() * 35 + 7;

                blocks.push_back(new_block);

                end_block = min((int)blocks.size(), max_blocks_to_show);
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

                    if (index_to_move < 0) index_to_move = 0;
                    if (index_to_move > blocks.size() - 1) index_to_move = blocks.size() - 1;

                    Block copy = blocks[i];
                    blocks.erase(blocks.begin() + i);
                    blocks.insert(blocks.begin() + index_to_move, copy);

                    for (int j = 0; j < blocks.size(); j++)
                    {
                        blocks[j].y = y + j * 35 + 7;
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

    OriginalBlocksManager(Sint16 _x, Sint16 _y, int w, int h, int count)
    {
        x = _x; y = _y; width = w; height = h; max_blocks_to_show = count;
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

    void manage_event(SDL_Event& e, BlockManager& manager)
    {
        if (original_blocks.empty()) return;
        for (int i = start_block; i < end_block; i++)
        {
            auto& it = original_blocks[i];
            it.manage_event(e);
            manager.handle_original(it);
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

#endif