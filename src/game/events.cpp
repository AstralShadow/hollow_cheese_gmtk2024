#include "game/game.hpp"
#include "core/core.hpp"
#include "game/data.hpp"
#include "world/render.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;

using world::drag_target;


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
#ifndef __EMSCRIPTEN__
    if(scancode == SDL_SCANCODE_Q)
        core::stop();
#endif
}

void game::keyup(SDL_KeyboardEvent&, scene_uid)
{
}


void game::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    if(enable_level_editor)
    {
        Rect btn_area {
            level_editor_btn.pos.x,
            level_editor_btn.pos.y,
            button_size.x,
            button_size.y
        };
        Point mouse {ev.x, ev.y};
        if(SDL_PointInRect(&mouse, &btn_area))
            if(level_editor_btn.action)
                level_editor_btn.action();
    }


    using world::world;
    drag_target = world::camera_pick_tile(world.levels[world.current_level].level, {ev.x, ev.y});
}

void game::mouseup(SDL_MouseButtonEvent&, scene_uid)
{
    drag_target.tile = nullptr;
}

void game::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    if(enable_level_editor)
    {
        Rect btn_area {
            level_editor_btn.pos.x,
            level_editor_btn.pos.y,
            button_size.x,
            button_size.y
        };
        Point mouse {ev.x, ev.y};
        level_editor_btn.focused = SDL_PointInRect(&mouse, &btn_area);
    }

    if(!drag_target.tile)
        return;

    world::scale_tile(drag_target, {ev.xrel, ev.yrel});
}

