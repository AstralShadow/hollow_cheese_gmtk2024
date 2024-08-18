#ifndef INCLUDE_WORLD_WORLD_HPP
#define INCLUDE_WORLD_WORLD_HPP

#include "world/level.hpp"

/// A world stores a grid of levels.
/// The grid is in pixels.
/// Levels snap based on common floor height

namespace world
{
    struct LevelData
    {
        Level level;
        Point pos; // on the grid in px
    };

    struct World
    {
        vector<LevelData> levels;
        int current_level = 0; // Keep in mind levels may be empty :(
    };
}

#endif // INCLUDE_WORLD_WORLD_HPP
