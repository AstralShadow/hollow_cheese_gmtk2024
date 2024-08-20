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

    if(obj->_label)
    {
        Rect label {
            (int) area.x + area.w / 2 - obj->_label_size.x / 2,
            (int) area.y - 16 - obj->_label_size.y,
            obj->_label_size.x,
            obj->_label_size.y
        };
        SDL_RenderCopy(rnd, obj->_label, nullptr, &label);
    }

    if(debug)
    {
        SDL_SetRenderDrawColor(rnd, 0x58, 0xd2, 0xff, 255);
        SDL_RenderDrawRectF(rnd, &area);

        if(obj->_name)
        {
            Rect name {
                (int) area.x + area.w / 2 - obj->_name_size.x / 2,
                (int) area.y + area.h + 16,
                obj->_name_size.x,
                obj->_name_size.y
            };
            SDL_RenderCopy(rnd, obj->_name, nullptr, &name);
        }
    }


    // TODO render label
}
