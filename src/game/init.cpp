#include "game/game.hpp"
#include "game/data.hpp"

namespace game
{
    Player player {
        .pos = {0, 0}
    };

    Map map;

    PickedTile drag_target;
}

void game::init(int, char**, scene_uid)
{
    const int size = 32;
    for(int i = 0; i < 20; i++)
        map.tiles.push_back(Tile{
            .area = {size * i, 500, size, size},
            .scalable = {1, 0, 0, 0}
        });

    map.tiles[10].scalable[TOP] = true;
}

void game::deinit(scene_uid)
{

}
