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
}

#endif // INCLUDE_GAME_DATA_HPP
