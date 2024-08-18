#ifndef INCLUDE_GAME_DATA_HPP
#define INCLUDE_GAME_DATA_HPP

#include "game/player.hpp"
#include "game/map.hpp"
#include <vector>

using std::vector;


namespace game
{
    extern vector<Player> players;
    extern Map map;
    extern PickedTile drag_target;

    void update_collisions(u32 ms, Map&, vector<Player>& players);
    void apply_tile_constraints(Map&);
    void apply_player_player_collisions(Player&);
    void apply_player_tile_collisions(u32 ms, Map&, Player&);
}

#endif // INCLUDE_GAME_DATA_HPP
