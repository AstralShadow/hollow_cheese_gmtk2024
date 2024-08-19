#include "game/game.hpp"
#include "game/data.hpp"
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
    /*
    const int size = 48;

    Level level;
    for(int i = 0; i < 20; i++)
        level.tiles.push_back(Tile
        {
            .area = {size * i, 304, size, size},
            .min_size = {16, 16},
            .scalable = {(i & 1) == 1, (i & 2) == 2, (i & 4) == 4, (i & 8) == 8}
        });

    level.tiles[10].scalable[TOP] = true;
    level.tiles[10].mandatory_area = level.tiles[10].area;

    world.levels.push_back({
        .level = level,
        .pos = {0, 0}
    });
    */
}

void game::deinit(scene_uid)
{

}
