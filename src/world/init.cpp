#include "world/scene.hpp"
#include "world/data.hpp"


namespace world
{
    World world;
    PickedTile drag_target;
}


void world::init(int, char**, scene_uid)
{
    load_world();
    world_update_reach_map(world);
}

void world::deinit(scene_uid)
{

}
