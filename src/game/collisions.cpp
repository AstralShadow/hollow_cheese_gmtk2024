#include "game/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::update_collisions(u32 ms, Level& level, vector<Player>& players)
{
    update_collisions(ms, level, players.begin(), players.end());
}

void game::update_collisions(u32 ms, Level& level, vector<Player>::iterator begin,
                                                   vector<Player>::iterator end)
{
    apply_tile_constraints(level);

    // When it comes to players, I think I'd prefer horizontal collisions applied first.

    //apply_player_player_collisions(Player&);

    while(begin != end)
    {
        apply_player_tile_collisions(ms, level, *(begin++));
        // deltaTime is used to adjust player velocity when giving them a push with a wall
        // (this is currently turned off)
    }


    for(auto& tile : level.tiles)
        tile.area_past = tile.area;

    for(auto& player : players)
        player.area_past = player.area;
}

// Note: Update jump reach simulation accordingly
