#include "world/level.hpp"

bool world::is_level_area_empty(Level const& level, SDL_Rect const& area)
{
    for(auto const& tile : level.tiles)
    {
        if(SDL_HasIntersection(&tile.area, &area))
            return false;
    }
    return true;
}
