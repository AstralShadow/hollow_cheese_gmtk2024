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


void WE::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    /* No levels notice */
    if(world::world.levels.size() == 0)
    {
        static SDL_Texture* notice = nullptr;
        static Rect area;
        if(!notice)
        {
            string text = "Welcome to the World Editor\n\n"
                          "There are no levels yet.\n"
                          "Please use the button \n"
                          "at the bottom right corner\n"
                          "to create one.";

            auto font = game::get_font();
            SDL_Color color {0x98, 0xd2, 0xff, 255};

            auto surf = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color , 0);
            if(!surf) {
                cout << "Failed to render notice" << endl;
                cout << TTF_GetError() << endl;
                return;
            }

            notice = utils::create_texture(surf);
            area = Rect {
                (WINDOW_WIDTH - surf->w) / 2,
                (WINDOW_HEIGHT - surf->h) / 2,
                surf->w,
                surf->h
            };

            SDL_FreeSurface(surf);
        }
        SDL_RenderCopy(rnd, notice, nullptr, &area);
    }
    else
    {
        static SDL_Texture* notice = nullptr;
        static Rect area;
        if(!notice)
        {
            string text = "Usage instructions\n\n"
                          "Click on a level tile to see actions.\n"
                          "    The last capital letter in action names \n"
                          "    can be used as keyboard hotkey.\n"
                          "Drag levels around to modify the world map.\n"
                          "If levels touch the player can transition between them ...\n"
                          "    ... as long as their contact area is not blocked.";

            auto font = game::get_font();
            SDL_Color color {0x98, 0xd2, 0xff, 255};

            auto surf = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, 0);
            if(!surf) {
                cout << "Failed to render notice 2" << endl;
                cout << TTF_GetError() << endl;
                return;
            }

            notice = utils::create_texture(surf);
            area = Rect {
                16,
                WINDOW_HEIGHT - surf->h - 16,
                surf->w,
                surf->h
            };

            SDL_FreeSurface(surf);
        }
        SDL_RenderCopy(rnd, notice, nullptr, &area);
    }


    {
        size_t temp = world::world.current_level;

        world::world.current_level = mouse_focus.level;
        world::render_world(world::world, true);

        world::world.current_level = temp;
    }

    if(mouse_focus.selected)
        render_level_tool_overlay();

    for(auto& btn : global_buttons)
        render_global_button(btn);

    // TODO add revisions and level names

    SDL_RenderPresent(rnd);
}
