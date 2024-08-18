#include "world/world.hpp"
#include "world/data.hpp"


namespace world
{
    Map map;
    PickedTile drag_target;
}


void world::init(int, char**, scene_uid)
{
    const int size = 48;
    for(int i = 0; i < 20; i++)
        map.tiles.push_back(Tile{
            .area = {size * i, 500, size, size},
            .min_size = {16, 16},
            .scalable = {i & 1, i & 2, i & 4, i & 8}
        });

    map.tiles[10].scalable[TOP] = true;
    map.tiles[10].mandatory_area = map.tiles[10].area;
}

void world::deinit(scene_uid)
{

}
