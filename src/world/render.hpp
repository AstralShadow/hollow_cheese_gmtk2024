#ifndef INCLUDE_WORLD_RENDER_HPP
#define INCLUDE_WORLD_RENDER_HPP

#include "world/world.hpp"

namespace world
{
    void render_level(Level const&);

    // Pick a tile to scale.
    // Only picks scalable sides unless ignoring constraints
    PickedTile camera_pick_tile(Level&, Point pos, bool ignore_scalable_constraints = false);


    struct PickedLevel
    {
        int level = -1;
        Rect area {0, 0, 0, 0};
        Point pos {0, 0}; // local
    };

    void render_world(World const&, bool ignore_exploration_flag = false);

    PickedLevel camera_pick_level(World const&, Point pos);
}

#endif // INCLUDE_WORLD_RENDER_HPP
