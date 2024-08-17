#ifndef INCLUDE_GAME_MAP_HPP
#define INCLUDE_GAME_MAP_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include "game/direction.hpp"
#include <vector>
#include <array>

using std::vector;
using std::array;


namespace game
{
    struct Tile
    {
        Rect area;
        Rect area_past = area; // past frame; used in collision detection

        // TODO add area where this block can scale into and min size

        array<bool, 4> scalable = {0};
    };

    struct Map
    {
        vector<Tile> tiles;
    };


    struct PickedTile
    {
        Tile* tile = nullptr;
        direction_t side = TOP; // Closest side to cursor
    };


    void scale_tile(PickedTile tile, Point delta);
    void normalize_tile(Tile& tile); // ensure no negative width/height
}

#endif // INCLUDE_GAME_MAP_HPP
