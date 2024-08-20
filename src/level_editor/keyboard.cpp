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


    if(scancode == SDL_SCANCODE_T)
        play_level();

    if(scancode == SDL_SCANCODE_C)
        toggle_player_count();

    if(scancode == SDL_SCANCODE_J)
        toggle_jump_prediction();


    if(scancode == SDL_SCANCODE_P)
        toggle_time_pause();

    if(scancode == SDL_SCANCODE_M)
        toggle_slow_motion();


    if(scancode == SDL_SCANCODE_B || scancode == SDL_SCANCODE_ESCAPE)
        open_world_editor();


#ifndef ESDF_CONTROLS
    if(scancode == SDL_SCANCODE_R)
        set_edit_mode();
#else
    if(scancode == SDL_SCANCODE_E)
        set_edit_mode();
#endif

    if(scancode == SDL_SCANCODE_O)
        set_object_mode();

    if(scancode == SDL_SCANCODE_T)
        set_texture_mode();
}

void LE::keyup(SDL_KeyboardEvent&, scene_uid)
{

}

