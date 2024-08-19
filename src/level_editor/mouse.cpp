#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;


void LE::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    if(ev.button == SDL_BUTTON_LEFT)
    {
        if(start_dragging_player_under_cursor({ev.x, ev.y}))
            return; // TODO possibly also "catch" players with click below them, if click was noop

        if(mode == EDIT_MODE)
        if(start_modifying_tiles({ev.x, ev.y}))
            return;
    }

    if(ev.button == SDL_BUTTON_RIGHT)
    {
        if(mode == EDIT_MODE)
        {
            removing_tiles = true;
            drag_tiles({ev.x, ev.y});
            cout << 'K' << endl;
        }
    }
}


void LE::mouseup(SDL_MouseButtonEvent& ev, scene_uid)
{
    if(ev.button == SDL_BUTTON_LEFT)
    {
        drop_dragged_players();
        drag_players({ev.x, ev.y}); // Needs to perform the actual drop, the above is a request

        if(mode == EDIT_MODE)
        {
            drag_tiles({ev.x, ev.y});
            stop_modifying_tiles({ev.x, ev.y});
        }
    }

    if(ev.button == SDL_BUTTON_RIGHT)
    {
        if(mode == EDIT_MODE && removing_tiles)
        {
            drag_tiles({ev.x, ev.y});
            removing_tiles = false;
        }
    }
}

void LE::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    drag_players({ev.x, ev.y});

    if(mode == EDIT_MODE)
    {
        drag_tiles({ev.x, ev.y}, {ev.xrel, ev.yrel});
    }
}


