#include "game/game.hpp"
#include "core/core.hpp"
#include "game/data.hpp"
#include "game/render.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
    if(scancode == SDL_SCANCODE_Q)
        core::stop();
}


void game::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    // TODO allow picking player when in level editor mode

    drag_target = camera_pick_tile(map, {ev.x, ev.y});
}

void game::mouseup(SDL_MouseButtonEvent&, scene_uid)
{
    drag_target.tile = nullptr;
}

void game::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    if(!drag_target.tile)
        return;

    scale_tile(drag_target, {ev.xrel, ev.yrel});
}

