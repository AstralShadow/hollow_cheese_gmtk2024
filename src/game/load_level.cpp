#include "game/data.hpp"
#include "core/scene.hpp"
#include "world/data.hpp"


void game::load_level(int index)
{
    // TODO pick player position based on previous level

    world.current_level = index;

    using world::world;

    if(world.current_level >= world.levels.size())
        core::set_scene("world_editor");
}
