#include "game/player.hpp"
#include <SDL2/SDL_keyboard.h>


void game::move_player(u64 ms, Player& player)
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
                motion.y += 1.0f;
                break;
            case LEFT:
                motion.x -= 1.0f;
                break;
        }
    }

    if(motion.x != 0 && motion.y != 0) {
        static const float sqrt2 = sqrt(2.0f);
        speed /= sqrt2;
    }

    player.area.x += motion.x * speed * ms;
    player.area.y += motion.y * speed * ms;
}
