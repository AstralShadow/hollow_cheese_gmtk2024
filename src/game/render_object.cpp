#include "core/core.hpp"
#include "game/object.hpp"
#include "game/sprite.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

static auto& rnd = core::renderer;


void game::render_object(Object const* obj, Point pos, float scale, bool debug)
{
    FRect area {
        pos.x * scale,
        pos.y * scale,
        obj->size.x * scale,
        obj->size.y * scale
    };

    if(!obj->sprite.empty())
    {
        auto texture = game::sprite(obj->sprite);
        SDL_RenderCopyF(rnd, texture, nullptr, &area);
    }

    if(debug)
    {
        SDL_SetRenderDrawColor(rnd, 0x58, 0xd2, 0xff, 255);
        SDL_RenderDrawRectF(rnd, &area);
    }


    // TODO render label
}
