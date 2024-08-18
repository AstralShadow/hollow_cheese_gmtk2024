#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world_editor/data.hpp"
#include "world/render.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;

static const Point level_size { WINDOW_WIDTH, WINDOW_HEIGHT };

void WE::mousedown(SDL_MouseButtonEvent&, scene_uid)
{
    if(mouse_focus.level == -1)
        return;

    mouse_focus.dragging = true;
}

void WE::mouseup(SDL_MouseButtonEvent&, scene_uid)
{
    mouse_focus.dragging = false;
}

void WE::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    if(mouse_focus.level != -1 && mouse_focus.dragging)
    {
        auto& world = world::world;

        FPoint scale {
            world.size.x * 1.0f / level_size.x,
            world.size.y * 1.0f / level_size.y
        };

        static FPoint buffer {0, 0};
        buffer.x += ev.xrel * scale.x;
        buffer.y += ev.yrel * scale.y;

        Point increment {
            static_cast<int>(buffer.x),
            static_cast<int>(buffer.y)
        };

        move_level(world, mouse_focus.level, increment);

        buffer.x -= increment.x;
        buffer.y -= increment.y;
    }
    else
    {
        auto pick = camera_pick_level(world::world, {ev.x, ev.y});

        mouse_focus.level = pick.level;
        mouse_focus.area = pick.area;
        mouse_focus.pos = pick.pos;
    }
}

