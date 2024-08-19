#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include "core/scene.hpp"
#include "game/data.hpp" // collisions
#include <iostream>

using std::cout;
using std::endl;


void LE::tick(u32 ms, scene_uid)
{
    if(!level()) // fall back to WE
        core::set_scene("world_editor");

    if(simulate_game)
    for(int i = 0; i < active_players; i++)
    {
        if(players_data[i].dragging)
            continue; // Skip players who are being dragged around

        auto itr = players.begin() + i;
        tick_players(ms, itr, itr + 1);
        update_collisions(ms, *level(), itr, itr + 1);
    }

    if(!simulate_game)
        update_collisions(ms, *level(), players.end(), players.end()); // I think i need the tile updates
}
