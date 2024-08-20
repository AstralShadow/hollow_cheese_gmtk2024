#ifndef INCLUDE_WORLD_WORLD_HPP
#define INCLUDE_WORLD_WORLD_HPP

#include "world/level.hpp"
#include <string>

using std::string;


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
        bool reachable = false; // TODO use in is_level_reachable
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

    /// Will prevent level overlaps. May snap to close levels logically.
    /// Sets delta to used delta. Works in world coords.
    void move_level(World&, int level, Point& delta);

    Point find_empty_level_pos(int close_to = -1);


    // World expect exactly one global player start area.
    // They also need positive amount of cheese (collectables)
    bool is_world_playable(World const&, string* message = nullptr);

    // Levels expect at least one player start area.
    // The closest one to the source map is picked
    bool is_level_playable(Level const&, string* message = nullptr);

    bool is_level_reachable(World const&, size_t level, vector<size_t>* ignore = nullptr);

    vector<size_t> get_level_neighbours(World const&, size_t level);

    void world_update_reach_map(World&); // TODO call on load


    constexpr int min_touch_distance = 50; // To count levels as linked
}

#endif // INCLUDE_WORLD_WORLD_HPP
