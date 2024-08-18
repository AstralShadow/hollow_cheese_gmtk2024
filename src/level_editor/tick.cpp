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
    {
        tick_players(ms, players.begin(), players.begin() + active_players);

        update_collisions(ms, *level(), players.begin(), players.begin() + active_players);
    }
}
