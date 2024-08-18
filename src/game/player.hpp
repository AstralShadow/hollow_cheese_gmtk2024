#ifndef INCLUDE_GAME_PLAYER_HPP
#define INCLUDE_GAME_PLAYER_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include "game/direction.hpp"
#include <SDL2/SDL_scancode.h>
#include <vector>

using std::vector;


namespace game
{
    struct Player
    {
        FRect area;
        FRect area_past = area; // past frame; used in collision detection
        // Note: we could lag the rendering a single frame and render the average of the 2 positions

        const float speed = 0.35f; // px/ms
        // const float steering_speed_in_air = 0.3f; // px/ms
        const float gravity = 3700.0f / 1000000; // px/ms^2
        const int step_height = 15;
        const int head_height = 10; // space from top ignored by horizontal wall collision

        const float jump_force = 1.1; // px/ms
        const int jump_delay_grace_time = 75; // ms
        const float early_jump_end_gravity_factor = 2.2f;

        FPoint velocity {0, 0}; // px/ms; horizontal is used in collision system
        bool has_foothold = false; // updated in collision system
        u64 last_foothold = 0; // used for jump delay grace time


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


    void tick_players(u32 ms, vector<Player>&);

    void move_player(u32 ms, Player&);
    void apply_player_gravity(u32 ms, Player&, bool early_jump_end);

}

#endif // INCLUDE_GAME_PLAYER_HPP
