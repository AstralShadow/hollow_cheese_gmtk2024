#include "world/level.hpp"


void world::reset_level(Level& level)
{
    reset_level_tiles(level);
}

void world::reset_level_tiles(Level& level)
{
    for(auto& tile : level.tiles)
    {
        tile.area = tile.original_area;
        tile.area_past = tile.original_area;
    }
}
