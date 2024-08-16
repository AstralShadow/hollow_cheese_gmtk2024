#ifndef INCLUDE_GAME_PLAYER_HPP
#define INCLUDE_GAME_PLAYER_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"

namespace game
{
    struct Player
    {
        FPoint pos;
        float speed = 5.0f;
    };
}

#endif // INCLUDE_GAME_PLAYER_HPP
