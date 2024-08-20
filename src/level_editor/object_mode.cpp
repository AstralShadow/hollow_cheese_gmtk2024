#include "level_editor/data.hpp"
#include "core/core.hpp"
#include "game/sprite.hpp"
#include "game/fonts.hpp"
#include "game/object.hpp"
#include "utils/textures.hpp"
#include "world/data.hpp"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

using game::sprite_size;

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
    if(drag_index == game::object(world_spawn_name) - &game::objects[0])
        world_spawn_exists = true;


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


    if(drag_index != -1)
    {
        Point pos;
        SDL_GetMouseState(&pos.x, &pos.y);

        auto const& obj = game::objects[drag_index];

        // TODO fix this being a bit off
        pos.x /= 0.8;
        pos.y /= 0.8;
        pos = pos - obj.size * (0.5 * 0.8);
        pos.x -= pos.x % 16;
        pos.y -= pos.y % 16;

        bool debug = true;
        render_object(&game::objects[drag_index], pos, 0.8, debug);
    }
}


bool LE::click_zone_object_mode(size_t index) // object_create
{
    drag_index = index;
    return true;
}


static size_t level_obj_at(world::Level const& level, Point pos)
{
    for(size_t i = 0; i < level.objects.size(); ++i)
    {
        auto obj = game::object(level.objects[i].name);
        if(!obj)
        {
            cout << "You got invalid object names" << endl;
            continue;
        }
        Rect area {
            level.objects[i].pos.x,
            level.objects[i].pos.y,
            obj->size.x,
            obj->size.y
        };
        if(SDL_PointInRect(&pos, &area))
            return i;
    }
    return -1;
}


bool LE::object_pick(Point cursor)
{
    Point pos = get_level_coordinates(cursor);
    int index = level_obj_at(*(level()), pos);
    if(index == -1)
        return false;

    string name = level()->objects[index].name;
    size_t oid = game::object(name) - &game::objects[0];
    drag_index = oid;

    cout << "erase pick" << endl;
    level()->objects.erase(level()->objects.begin() + index);
    return true;
}

void LE::object_drag(Point)
{
    // noop, all in rendering
    // TODO do the request-to-drop approach as with players
}

void LE::object_drop(Point cursor)
{
    if(drag_index == -1)
        return;

    Point pos = get_level_coordinates(cursor);

    auto const& obj = game::objects[drag_index];

    pos = pos - obj.size * 0.5;
    pos.x -= pos.x % 16;
    pos.y -= pos.y % 16;

    level()->objects.push_back({
        obj.name,
        pos
    });

    drag_index = -1;
}

void LE::object_remove(Point cursor)
{
    if(!drag_remove)
        return;

    Point pos = get_level_coordinates(cursor);
    int index = level_obj_at(*(level()), pos);
    if(index == -1)
        return;

    cout << "erase del" << endl;
    level()->objects.erase(level()->objects.begin() + index);
}


