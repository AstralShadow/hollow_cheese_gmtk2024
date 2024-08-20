#include "menu/menu.hpp"
#include "core/core.hpp"
#include "utils/point.hpp"
#include "core/scene.hpp"
#include <SDL2/SDL_events.h>


void menu::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
#ifndef __EMSCRIPTEN__
    if(scancode == SDL_SCANCODE_Q)
        core::stop();
#endif // __EMSCRIPTEN__
}

void menu::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    Point mouse {ev.x, ev.y};
    Rect play {
        66, 200, 317, 136
    };

    Rect world_editor {
        198 / 3, 1300 / 3, 958 / 3, 380 / 3
    };

    if(SDL_PointInRect(&mouse, &play))
        core::set_scene("game");

    if(SDL_PointInRect(&mouse, &world_editor))
        core::set_scene("world_editor");
}
