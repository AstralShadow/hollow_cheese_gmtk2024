#ifndef INCLUDE_GAME_RENDER_HPP
#define INCLUDE_GAME_RENDER_HPP

#include "game/map.hpp"

namespace game
{
    void render_level(Map const& map);
    PickedTile camera_pick_tile(Map& map, Point pos, bool ignore_scalable_constraints = false);
}

#endif // INCLUDE_GAME_RENDER_HPP
