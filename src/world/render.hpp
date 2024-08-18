#ifndef INCLUDE_WORLD_RENDER_HPP
#define INCLUDE_WORLD_RENDER_HPP

#include "world/map.hpp"

namespace world
{
    void render_map(Map const&);

    // Pick a tile to scale.
    // Only picks scalable sides unless ignoring constraints
    PickedTile camera_pick_tile(Map&, Point pos, bool ignore_scalable_constraints = false);
}

#endif // INCLUDE_WORLD_RENDER_HPP
