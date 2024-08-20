#ifndef INCLUDE_WORLD_DATA_HPP
#define INCLUDE_WORLD_DATA_HPP

#include "world/world.hpp"
#include <vector>

using std::vector;


namespace world
{
    // drag_target is only meaningful in Level scope.
    // There won't be more than one level focused, so it can stay as global variable.
    extern PickedTile drag_target;

    extern World world;


    void save_world();
    void load_world();
}

#endif // INCLUDE_WORLD_DATA_HPP
