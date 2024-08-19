#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include "game/render.hpp"
#include <SDL2/SDL_events.h>


namespace LE
{
    static void drag_players(Point mouse_pos_in_level);
}


void LE::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    Point pos = get_level_coordinates({ev.x, ev.y});

    int i = camera_pick_player_idx(players, pos);
    if(i != -1 && i < active_players)
    {
        players_data[i].dragging = true;
        players_data[i].drag_offset = {
            static_cast<int>(players[i].area.x - pos.x),
            static_cast<int>(players[i].area.y - pos.y)
        };
        players[i].velocity.y = 0;
        players[i].has_foothold = false;
    }
}

void LE::mouseup(SDL_MouseButtonEvent& ev, scene_uid)
{
    for(int i = 0; i < active_players; ++i)
        if(players_data[i].dragging)
            players_data[i].plan_to_drop = true;

    Point pos = get_level_coordinates({ev.x, ev.y});
    drag_players(pos);
}

void LE::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    Point pos = get_level_coordinates({ev.x, ev.y});
    drag_players(pos);
}

void LE::drag_players(Point mouse_pos_in_level)
{
    auto const pos = mouse_pos_in_level;

    for(int i = 0; i < active_players; ++i)
    {
        if(!players_data[i].dragging)
            continue;
        players[i].area.x = pos.x + players_data[i].drag_offset.x;
        players[i].area.y = pos.y + players_data[i].drag_offset.y;

        if(!players_data[i].plan_to_drop)
            continue;

        SDL_Rect area
        {
            static_cast<int>(players[i].area.x),
            static_cast<int>(players[i].area.y),
            static_cast<int>(players[i].area.w) + 1,
            static_cast<int>(players[i].area.h) + 1
        };

        if(!world::is_level_area_empty(*(level()), area))
            continue;

        players_data[i].dragging = false;
        players_data[i].plan_to_drop = false;
    }
}

