#include "level_editor/data.hpp"
#include "game/render.hpp"


bool LE::start_dragging_player_under_cursor(Point cursor)
{
    Point pos = get_level_coordinates(cursor);

    int i = camera_pick_player_idx(players, pos);
    if(i == -1 || i >= active_players)
        return false;

    players[i].velocity.y = 0;
    players[i].has_foothold = false;

    players_data[i].dragging = true;
    players_data[i].drag_offset = {
        static_cast<int>(players[i].area.x - pos.x),
        static_cast<int>(players[i].area.y - pos.y)
    };

    return true;
}

void LE::drag_players(Point cursor)
{
    Point pos = get_level_coordinates(cursor);

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

void LE::drop_dragged_players()
{
    for(int i = 0; i < active_players; ++i)
        if(players_data[i].dragging)
            players_data[i].plan_to_drop = true;
}
