#ifndef INCLUDE_WORLD_RENDER_HPP
#define INCLUDE_WORLD_RENDER_HPP

#include "world/level.hpp"

namespace world
{
    void render_level(Level const&);

    // Pick a tile to scale.
    // Only picks scalable sides unless ignoring constraints
    PickedTile camera_pick_tile(Level&, Point pos, bool ignore_scalable_constraints = false);
}

#endif // INCLUDE_WORLD_RENDER_HPP
