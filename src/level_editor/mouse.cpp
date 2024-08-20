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

        if(mode == OBJECT_MODE)
        if(object_pick({ev.x, ev.y}))
            return;

        if(mode == TEXTURE_MODE)
        if(texture_pick({ev.x, ev.y}))
            return;
    }

    if(ev.button == SDL_BUTTON_RIGHT)
    {
        if(mode == EDIT_MODE)
        {
            drag_remove = true;
            drag_tiles({ev.x, ev.y});
        }

        if(mode == OBJECT_MODE)
        {
            drag_remove = true;
            object_drag({ev.x, ev.y});
        }

        if(mode == TEXTURE_MODE)
        {
            drag_remove = true;
            texture_drag({ev.x, ev.y});
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
        if(mode == OBJECT_MODE)
        {
            object_drag({ev.x, ev.y});
            object_drop({ev.x, ev.y});
        }

        if(mode == TEXTURE_MODE)
        {
            texture_drag({ev.x, ev.y});
            texture_drop({ev.x, ev.y});
        }
    }

    if(ev.button == SDL_BUTTON_RIGHT && drag_remove)
    {
        if(mode == EDIT_MODE)
        {
            drag_tiles({ev.x, ev.y});
            drag_remove = false;
        }
        if(mode == OBJECT_MODE)
        {
            object_drag({ev.x, ev.y});
            drag_remove = false;
        }
        if(mode == TEXTURE_MODE)
        {
            texture_drag({ev.x, ev.y});
            drag_remove = false;
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
    if(mode == OBJECT_MODE)
    {
        object_remove({ev.x, ev.y});
    }
    if(mode == TEXTURE_MODE)
    {
        texture_remove({ev.x, ev.y});
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

    if(menu_scroll > menu_content_height - menu_area.h / 2)
        menu_scroll = menu_content_height - menu_area.h / 2;

    if(menu_scroll < 0)
        menu_scroll = 0;
}


