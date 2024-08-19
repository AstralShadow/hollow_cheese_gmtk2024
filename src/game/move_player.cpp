#include "game/player.hpp"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_timer.h>
#include <iostream>

using std::cout;
using std::endl;


void game::move_player(u32 ms, Player& player, bool artifical_motion)
{
    auto const* state = SDL_GetKeyboardState(nullptr);

    FPoint motion {0.0f, 0.0f};
    float speed = player.speed;

    if(!artifical_motion)
    {
        for(u8 i = 0; i < 4; i++)
        {
            if(!state[player.controls[i]])
                continue;

            switch(i)
            {
                case TOP:
                    motion.y -= 1.0f;
                    break;
                case RIGHT:
                    motion.x += 1.0f;
                    break;
                case BOTTOM:
                    // Will be used for other stuff, like actions
                    break;
                case LEFT:
                    motion.x -= 1.0f;
                    break;
            }
        }
        player.velocity.x = motion.x;
    }

    player.area.x += player.velocity.x * speed * ms;

    // Jumping
    if(motion.y < 0)
    {
        int delay = SDL_GetTicks64() - player.last_foothold;
        if(delay < player.jump_delay_grace_time) {
            player.velocity.y = -player.jump_force;
            player.has_foothold = false;
            player.last_foothold = SDL_GetTicks64() - player.jump_delay_grace_time;
        }
    }

    apply_player_gravity(ms, player, motion.y == 0.0f && !artifical_motion);
}

void game::apply_player_gravity(u32 ms, Player& player, bool early_jump_end)
{
    if(player.has_foothold) {
        if(player.velocity.y > 0.0f)
            player.velocity.y = 0.0f;
        player.last_foothold = SDL_GetTicks64();
        return;
    }

    float speed_progress = player.gravity * ms;
    if(early_jump_end && player.velocity.y < 0.0f)
        speed_progress *= player.early_jump_end_gravity_factor;

    float speed_avr = player.velocity.y + speed_progress / 2;
    player.velocity.y += speed_progress;

    player.area.y += speed_avr * ms;
}

