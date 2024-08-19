#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include <SDL2/SDL_events.h>


void LE::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    if(start_dragging_player_under_cursor({ev.x, ev.y}))
        return; // TODO possibly also "catch" players with click below them, if click was noop

}


void LE::mouseup(SDL_MouseButtonEvent& ev, scene_uid)
{
    drop_dragged_players();
    drag_players({ev.x, ev.y}); // Needs to perform the actual drop, the above is a request
}

void LE::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    drag_players({ev.x, ev.y});
}


