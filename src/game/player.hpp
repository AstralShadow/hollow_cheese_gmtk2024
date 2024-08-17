#ifndef INCLUDE_GAME_PLAYER_HPP
#define INCLUDE_GAME_PLAYER_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include "game/direction.hpp"
#include <SDL2/SDL_scancode.h>

namespace game
{
    struct Player
    {
        FRect area;
        FRect area_past = area; // past frame; used in collision detection

        const float speed = 0.3f; // px/ms
        const int step_size = 10;

        const SDL_Scancode controls[4] = { // top, right, bottom, left
        #ifndef ESDF_CONTROLS
            SDL_SCANCODE_W,
            SDL_SCANCODE_D,
            SDL_SCANCODE_S,
            SDL_SCANCODE_A,
        #else // ESDF_CONTROLS
            SDL_SCANCODE_E,
            SDL_SCANCODE_F,
            SDL_SCANCODE_D,
            SDL_SCANCODE_S,
        #endif
        };
    };

    void move_player(u64 ms, Player& player);

    inline void tick_player(u64 ms, Player& p)
    {
        move_player(ms, p);
    }
}

#endif // INCLUDE_GAME_PLAYER_HPP
