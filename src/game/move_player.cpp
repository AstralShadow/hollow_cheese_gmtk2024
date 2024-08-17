#include "game/player.hpp"
#include <SDL2/SDL_keyboard.h>
#include <iostream>

using std::cout;
using std::endl;


void game::move_player(u32 ms, Player& player)
{
    auto const* state = SDL_GetKeyboardState(nullptr);

    FPoint motion {0.0f, 0.0f};
    float speed = player.speed;

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
                //motion.y += 1.0f;
                break;
            case LEFT:
                motion.x -= 1.0f;
                break;
        }
    }

    //if(motion.x != 0 && motion.y != 0) {
    //    static const float sqrt2 = sqrt(2.0f);
    //    speed /= sqrt2;
    //}

    player.area.x += motion.x * speed * ms;
    //player.area.y += motion.y * speed * ms;

    player.velocity.x = motion.x; // Store for collisions to later access

    apply_player_gravity(ms, player);
}

void game::apply_player_gravity(u32 ms, Player& player)
{
    if(player.has_foothold) {
        if(player.velocity.y > 0.0f)
            player.velocity.y = 0.0f;
        return;
    }

    float speed_avr = player.velocity.y + ms * player.gravity / 2;
    player.velocity.y += ms * player.gravity / 2;

    player.area.y += speed_avr * ms;
}

