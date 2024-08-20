#include "level_editor/data.hpp"
#include "core/core.hpp"
#include "game/sprite.hpp"
#include "game/fonts.hpp"
#include "utils/textures.hpp"
#include "world/data.hpp"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <iostream>

using std::cout;
using std::endl;
using std::array;

using game::sprite_size;
using game::sprite;

static const string textures[] {
    // Behind
    "top decoration double deer",
    "top decoration holy cheese",
    "chain",

    // Front
    "ground",
    "ground-wall-dark",
    "ground-lower-part",
    "lower-part",
    "ground-middle-part",
    "middle-part",
    "ground-full-part",
    "full-part",
    "ground-wall-light",
    "lower-part-right-end",
    "lower-part-left-end"
};




static auto& rnd = core::renderer;

void LE::render_texture_mode_menu()
{
    /* Title */
    static SDL_Texture* title = nullptr;
    static Point tsize {0, 0};
    if(!title)
    {
        auto font = game::get_font();

        const SDL_Color color {0x98, 0xd2, 0xff, 255};
        auto surf = TTF_RenderUTF8_Blended(font, "Textures:", color);
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


    int menu_height = 8;
    menu_zones.clear(); // TODO don't regenerate this data every time?

    size_t index = 0;
    for(auto name : textures)
    {
        auto size = sprite_size(name);

        Rect area {
            _area.x + 8,
            _area.y + menu_height - menu_scroll,
            size.x, size.y
        };

        menu_height += 8 + area.h;

        if(area.y + area.h < _area.y)
            continue;
        if(area.y > _area.y + _area.h)
            continue;

        SDL_RenderCopy(rnd, sprite(name), nullptr, &area);
        menu_zones.push_back(MenuZone {
            .area = area,
            .index = index
        });

        index++;
    }
    menu_content_height = menu_height;


    SDL_RenderSetClipRect(rnd, nullptr);

    SDL_SetRenderDrawColor(rnd, 0x00, 0x5d, 0x93, 255);
    SDL_RenderDrawRect(rnd, &_area);


    if(!drag_texture.empty())
    {
        Rect area;
        string name = drag_texture;
        auto size = sprite_size(name);
        SDL_GetMouseState(&area.x, &area.y);

        area.x -= size.x * (0.5 * 0.8);
        area.y -= size.y * (0.5 * 0.8);
        area.w = size.x * 0.8;
        area.h = size.y * 0.8;

        SDL_RenderCopy(rnd, sprite(name), nullptr, &area);

        SDL_SetRenderDrawColor(rnd, 0x58, 0xd2, 0xff, 255);
        SDL_RenderDrawRect(rnd, &area);
    }
}


bool LE::click_zone_texture_mode(size_t index) // object_create
{
    drag_texture = textures[index];
    return true;
}


static int level_tex_at(world::Level const& level, Point pos)
{
    for(size_t i = 0; i < level.textures.size(); ++i)
    {
        auto sprite = game::sprite(level.textures[i].name);
        auto size = sprite_size(sprite);
        if(!sprite)
        {
            cout << "You got invalid sprite names" << endl;
            continue;
        }

        Rect area {
            level.textures[i].pos.x,
            level.textures[i].pos.y,
            size.x,
            size.y
        };
        if(SDL_PointInRect(&pos, &area))
            return i;
    }
    return -1;
}


bool LE::texture_pick(Point cursor)
{
    Point pos = get_level_coordinates(cursor);
    int index = level_tex_at(*(level()), pos);
    if(index == -1)
        return false;

    drag_texture = level()->textures[index].name;

    level()->textures.erase(level()->textures.begin() + index);
    return true;
}

void LE::texture_drag(Point)
{
    // noop, all in rendering
    // TODO do the request-to-drop approach as with players
}

void LE::texture_drop(Point cursor)
{
    if(drag_texture.empty())
        return;

    Point pos = get_level_coordinates(cursor);

    auto name = drag_texture;
    auto size = sprite_size(drag_texture);

    pos = pos - size * 0.5;

    level()->textures.push_back({
        name,
        pos
    });

    drag_texture = "";
}

void LE::texture_remove(Point cursor)
{
    if(!drag_remove)
        return;

    Point pos = get_level_coordinates(cursor);
    int index = level_tex_at(*(level()), pos);
    if(index == -1)
        return;

    level()->textures.erase(level()->textures.begin() + index);
}


