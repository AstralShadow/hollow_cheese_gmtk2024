#include "level_editor/data.hpp"
#include "core/core.hpp"
#include "game/fonts.hpp"
#include "game/object.hpp"
#include "utils/textures.hpp"
#include "world/data.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

static auto& rnd = core::renderer;

void LE::render_object_mode_menu()
{
    /* Title */
    static SDL_Texture* title = nullptr;
    static Point tsize {0, 0};
    if(!title)
    {
        auto font = game::get_font();

        const SDL_Color color {0x98, 0xd2, 0xff, 255};
        auto surf = TTF_RenderUTF8_Blended(font, "Objects:", color);
        if(!surf) {
            cout << "Failed to render title" << endl;
            cout << TTF_GetError() << endl;
        }

        title = utils::create_texture(surf),
        tsize.x = surf->w;
        tsize.y = surf->h;

        SDL_FreeSurface(surf);
    }

    Rect tarea
    {
        menu_area.x,
        menu_area.y,
        tsize.x, tsize.y
    };

    SDL_RenderCopy(rnd, title, nullptr, &tarea);


    /* Object list */

    const Rect _area {
        menu_area.x,
        menu_area.y + tsize.y + 16,
        menu_area.w,
        menu_area.h - tsize.y - 16
    };
    SDL_SetRenderDrawColor(rnd, 0x05, 0x12, 0x1a, 196);
    SDL_RenderFillRect(rnd, &_area);

    SDL_RenderSetClipRect(rnd, &_area);


    const string world_spawn_name = "game_start_point";
    bool world_spawn_exists = is_world_playable(world::world);


    int menu_height = 8;
    menu_zones.clear(); // TODO don't regenerate this data every time?

    for(size_t index = 0; index < game::objects.size(); ++index)
    {
        auto const& obj = game::objects[index];

        if(world_spawn_exists && obj.name == world_spawn_name)
            continue; // Cap to one world spawn

        Rect area {
            _area.x + 8,
            _area.y + menu_height - menu_scroll,
            obj._name_size.x,
            obj._name_size.y
        };

        menu_height += 8 + area.h;

        if(area.y + area.h < _area.y)
            continue;
        if(area.y > _area.y + _area.h)
            continue;

        SDL_RenderCopy(rnd, obj._name, nullptr, &area);
        menu_zones.push_back(MenuZone {
            .area= area,
            .index = index
        });
    }
    menu_content_height = menu_height;


    SDL_RenderSetClipRect(rnd, nullptr);

    SDL_SetRenderDrawColor(rnd, 0x00, 0x5d, 0x93, 255);
    SDL_RenderDrawRect(rnd, &_area);
}


bool LE::click_zone_object_mode(size_t index)
{
    auto& obj = game::objects[index];

    cout << "clicked at '" << obj.name << "'" << endl;

    return true;
}
