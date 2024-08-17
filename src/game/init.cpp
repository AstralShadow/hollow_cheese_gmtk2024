#include "game/game.hpp"
#include "game/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


namespace game
{
    vector<Player> players {
        Player{
            .area = {0, 0, 32, 64}
        },
        {
            .area = {128, 0, 32, 64},
            .controls = {
                SDL_SCANCODE_UP,
                SDL_SCANCODE_RIGHT,
                SDL_SCANCODE_DOWN,
                SDL_SCANCODE_LEFT
            }
        }
    };

    Map map;

    PickedTile drag_target;
}


void game::init(int, char**, scene_uid)
{
    const int size = 48;
    for(int i = 0; i < 20; i++)
        map.tiles.push_back(Tile{
            .area = {size * i, 500, size, size},
            .min_size = {10, 10},
            .scalable = {i & 1, i & 2, i & 4, i & 8}
        });

    map.tiles[10].scalable[TOP] = true;
}

void game::deinit(scene_uid)
{

}
