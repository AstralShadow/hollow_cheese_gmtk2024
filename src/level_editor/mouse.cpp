#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;


void LE::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    last_action_error = "";
    if(click_button({ev.x, ev.y}))
        return;

    if(click_zone({ev.x, ev.y}))
        return;

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
    if(button_on_pos({ev.x, ev.y}))
        return;

    if(zone_on_pos({ev.x, ev.y}))
        return;

    if(ev.button == SDL_BUTTON_LEFT)
    {
        drop_dragged_players(); // TODO rename to sth that contains request
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


    /* Buttons */
    for(auto& btn : buttons)
        btn.focused = false;
    for(auto& btn : mode_buttons)
        btn.focused = false;

    auto btn = button_on_pos({ev.x, ev.y});
    if(btn)
        btn->focused = true;
}

void LE::mouse_wheel(SDL_MouseWheelEvent& ev, scene_uid)
{
    menu_scroll -= ev.y * 64; // I'd expect a full finger slide to scroll nearly a page.

    if(menu_scroll > menu_content_height - menu_area.h)
        menu_scroll = menu_content_height - menu_area.h;

    if(menu_scroll < 0)
        menu_scroll = 0;
}


