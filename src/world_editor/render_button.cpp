#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world/render.hpp"
#include "world_editor/data.hpp"
#include "game/fonts.hpp"
#include "utils/textures.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

static auto& rnd = core::renderer;


void WE::generate_button_label(Button& btn)
{
    if(!btn.label_texture) {
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


void WE::render_level_button(Button const& btn)
{
    Rect area {
        mouse_focus.area.x + (btn.pos.x >= 0) * (mouse_focus.area.w) + btn.pos.x,
        mouse_focus.area.y + (btn.pos.y < 0) * (mouse_focus.area.h) + btn.pos.y,
        button_size.x, button_size.y
    };
    if(btn.pos.x < 0)
        area.x -= area.w;
    if(btn.pos.y < 0)
        area.y -= area.h;

    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderFillRect(rnd, &area);

    if(btn.focused)
        SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(rnd, 128, 128, 128, 255);

    SDL_RenderDrawRect(rnd, &area);


    /* Render label */

    if(btn.focused)
    {
        SDL_Rect dest {
            area.x + (btn.pos.x > 0 ? area.w + 4 : -btn.label_size.x - 4),
            area.y + area.h / 2 - btn.label_size.y / 2,
            btn.label_size.x,
            btn.label_size.y
        };

        SDL_RenderCopy(rnd, btn.label_texture, nullptr, &dest);
    }
}

void WE::render_global_button(Button const& btn)
{
    Rect area {
        btn.pos.x + (btn.pos.x < 0) * (WINDOW_WIDTH - button_size.x),
        btn.pos.y + (btn.pos.y < 0) * (WINDOW_HEIGHT - button_size.y),
        button_size.x, button_size.y
    };

    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderFillRect(rnd, &area);

    if(btn.focused)
        SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(rnd, 128, 128, 128, 255);

    SDL_RenderDrawRect(rnd, &area);


    /* Render label */

    if(btn.focused)
    {
        SDL_Rect dest {
            area.x + (btn.pos.x > 0 ? button_size.x + 4 : -btn.label_size.x - 4),
            area.y + area.h / 2 - btn.label_size.y / 2,
            btn.label_size.x,
            btn.label_size.y
        };

        SDL_RenderCopy(rnd, btn.label_texture, nullptr, &dest);
    }
}
