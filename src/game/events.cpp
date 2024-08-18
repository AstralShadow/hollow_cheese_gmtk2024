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
    if(scancode == SDL_SCANCODE_Q)
        core::stop();

    if(scancode == SDL_SCANCODE_P)
        core::slow_motion = !core::slow_motion;
}

void game::mousedown(SDL_MouseButtonEvent&, scene_uid)
{
    // TODO allow picking player when in level editor mode

    //drag_target = world::camera_pick_tile(world::map, {ev.x, ev.y});
    throw new std::runtime_error("Text level is in shmittereens");
}

void game::mouseup(SDL_MouseButtonEvent&, scene_uid)
{
    drag_target.tile = nullptr;
}

void game::mouse_motion(SDL_MouseMotionEvent&, scene_uid)
{
    //if(!drag_target.tile)
    //    return;

    //scale_tile(drag_target, {ev.xrel, ev.yrel});
}

