#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world_editor/data.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;


void WE::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
    if(scancode == SDL_SCANCODE_Q)
        core::stop();

    if(mouse_focus.level == -1)
        return;

    if(scancode == SDL_SCANCODE_D)
        delete_level();

    if(scancode == SDL_SCANCODE_C)
        clone_level();

    if(scancode == SDL_SCANCODE_I || scancode == SDL_SCANCODE_E)
        edit_level();
}
