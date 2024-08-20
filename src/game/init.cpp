#include "game/game.hpp"
#include "game/data.hpp"
#include "game/sprite.hpp"
#include <iostream>

using std::cout;
using std::endl;


namespace game
{
    vector<Player> players {
        Player{
            .area = {0, 200, 32, 64}
        },
        {
            .area = {128, 200, 32, 64},
            .controls = {
                SDL_SCANCODE_UP,
                SDL_SCANCODE_RIGHT,
                SDL_SCANCODE_DOWN,
                SDL_SCANCODE_LEFT
            }
        }
    };
}


void game::init(int, char**, scene_uid)
{
    init_sprites();
}

void game::deinit(scene_uid)
{

}
