#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_events.h>


void LE::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
#ifndef __EMSCRIPTEN__
    if(scancode == SDL_SCANCODE_Q)
        core::stop();
#endif // __EMSCRIPTEN__

}

void LE::keyup(SDL_KeyboardEvent&, scene_uid)
{

}

