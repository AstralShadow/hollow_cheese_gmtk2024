#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world_editor/data.hpp"
#include "world/render.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;


void WE::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{

}

void WE::mouseup(SDL_MouseButtonEvent&, scene_uid)
{

}

void WE::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    auto pick = camera_pick_level(world::world, {ev.x, ev.y});

    mouse_focus.level = pick.level;
    mouse_focus.area = pick.area;
    mouse_focus.pos = pick.pos;
}

