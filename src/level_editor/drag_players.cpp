#include "level_editor/data.hpp"
#include "game/render.hpp"
#include <SDL2/SDL_mouse.h>


bool LE::start_dragging_player_under_cursor(Point cursor)
{
    Point pos = get_level_coordinates(cursor);

    int i = camera_pick_player_idx(players, pos);
    if(i == -1 || i >= active_players)
        return false;

    // Reset some vars
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


void LE::toggle_player_count(int count)
{
    if(count < -1)
        return;
    if(count == -1)
        count = (active_players + 1) % (1 + players.size());
    if(count > (int) players.size())
        count = players.size();

    active_players = count;
    if(count == 0)
        return;


    auto& player = players[active_players - 1];
    auto& data = players_data[active_players - 1];

    // Reset some vars
    player.velocity.y = 0;
    player.has_foothold = false;

    data.dragging = true;
    data.drag_offset = {
        static_cast<int>(-player.area.w / 2),
        static_cast<int>(-player.area.h / 2)
    };

    SDL_Point _mouse;
    SDL_GetMouseState(&_mouse.x, &_mouse.y);
    drag_players(_mouse);
}

