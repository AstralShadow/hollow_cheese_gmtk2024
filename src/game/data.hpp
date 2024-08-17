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

    void update_collisions(Map&, vector<Player>& players);
    void apply_tile_constraints(Map&);
}

#endif // INCLUDE_GAME_DATA_HPP
