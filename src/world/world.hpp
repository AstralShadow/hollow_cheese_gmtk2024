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

        bool explored = false; // If the player has been here
    };

    struct World
    {
        vector<LevelData> levels;
        size_t current_level = 0; // Keep in mind levels may be empty :(

        const Point size = {
            WINDOW_WIDTH * 7,
            WINDOW_HEIGHT * 7
        };
    };

    void move_level(World&, int level, Point& delta); // sets delta to used delta, in world coords
}

#endif // INCLUDE_WORLD_WORLD_HPP
