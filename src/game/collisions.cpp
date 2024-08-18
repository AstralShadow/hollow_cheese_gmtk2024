#include "game/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::update_collisions(u32 ms, Map& map, vector<Player>& players)
{
    apply_tile_constraints(map);

    // When it comes to players, I think I'd prefer horizontal collisions applied first.

    //apply_player_player_collisions(Player&);

    for(auto& player : players)
    {
        apply_player_tile_collisions(ms, map, player);
        // deltaTime is used to adjust player velocity when giving them a push with a wall
        // (this is currently turned off)
    }


    for(auto& tile : map.tiles)
        tile.area_past = tile.area;

    for(auto& player : players)
        player.area_past = player.area;
}


