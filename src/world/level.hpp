#ifndef INCLUDE_WORLD_LEVEL_HPP
#define INCLUDE_WORLD_LEVEL_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include "game/direction.hpp"
#include <vector>
#include <array>

using std::vector;
using std::array;


namespace world
{
    struct Tile
    {
        Rect area;
        Rect area_past = area; // past frame; used in collision detection
        Rect original_area = area; // modified in level editor. Used when saving

        Point min_size {0, 0}; // 0x0 = none
        Rect mandatory_area {0, 0, 0, 0}; // size 0x0 = not used

        array<bool, 4> scalable = {0};
    };

    struct Level
    {
        vector<Tile> tiles;
    };


    struct PickedTile
    {
        Tile* tile = nullptr;
        direction_t side = static_cast<direction_t>(0); // Closest side to cursor
    };


    void scale_tile(PickedTile tile, Point delta);
    void normalize_tile(Tile& tile); // ensure no negative width/height

    bool is_level_area_empty(Level const&, SDL_Rect const& area);

    void reset_level(Level&);
    void reset_level_tiles(Level&);
}

#endif // INCLUDE_WORLD_LEVEL_HPP
