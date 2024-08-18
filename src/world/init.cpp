#include "world/scene.hpp"
#include "world/data.hpp"


namespace world
{
    World world;
    PickedTile drag_target;
}


void world::init(int, char**, scene_uid)
{
    const int size = 48;

    Level level;
    for(int i = 0; i < 20; i++)
        level.tiles.push_back(Tile{
            .area = {size * i, 300, size, size},
            .min_size = {16, 16},
            .scalable = {i & 1, i & 2, i & 4, i & 8}
        });

    level.tiles[10].scalable[TOP] = true;
    level.tiles[10].mandatory_area = level.tiles[10].area;

    world.levels.push_back({
        .level = level,
        .pos = {0, 0}
    });
}

void world::deinit(scene_uid)
{

}
