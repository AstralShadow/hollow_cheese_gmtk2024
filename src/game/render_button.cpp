#include "game/button.hpp"
#include "core/core.hpp"
#include "game/fonts.hpp"
#include "utils/textures.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

static auto& rnd = core::renderer;


void game::generate_button_label(Button& btn)
{
    if(!btn.label_texture)
    {
        auto font = game::get_font();
        SDL_Color white {255, 255, 255, 255};

        auto surf = TTF_RenderUTF8_Blended(font, btn.label.c_str(), white);
        if(!surf) {
            cout << "Failed to render button label" << endl;
            cout << TTF_GetError() << endl;
            return;
        }

        btn.label_texture = utils::create_texture(surf);
        btn.label_size = {surf->w, surf->h};

        SDL_FreeSurface(surf);
    }
}


void game::render_button(Button const& btn, Rect const& area)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderFillRect(rnd, &area);

    if(btn.focused)
        SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(rnd, 128, 128, 128, 255);

    SDL_RenderDrawRect(rnd, &area);
}

void game::render_button(Button const& btn, Point const& pos)
{
    SDL_Rect area {
        pos.x,
        pos.y,
        button_size.x,
        button_size.y
    };
    render_button(btn, area);
}


void game::render_button_label(Button const& btn, Rect const& label_area)
{
    SDL_RenderCopy(rnd, btn.label_texture, nullptr, &label_area);
}

void game::render_button_label(Button const& btn, Point const& label_pos)
{
    SDL_Rect area {
        label_pos.x,
        label_pos.y,
        btn.label_size.x,
        btn.label_size.y
    };

    render_button_label(btn, area);
}
