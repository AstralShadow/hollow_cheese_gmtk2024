#ifndef INCLUDE_GAME_DATA_HPP
#define INCLUDE_GAME_DATA_HPP

#include "game/player.hpp"
#include "game/map.hpp"

namespace game
{
    extern Player player;
    extern Map map;
    extern PickedTile drag_target;
}

#endif // INCLUDE_GAME_DATA_HPP
