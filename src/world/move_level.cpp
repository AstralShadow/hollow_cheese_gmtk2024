#include "world/world.hpp"
#include <cmath>

using std::abs;


void world::move_level(World& world, int _level, Point& delta)
{
    auto const& wsize = world.size;
    auto& level = world.levels[_level];
    auto& pos = level.pos;
    const Point lsize { WINDOW_WIDTH, WINDOW_HEIGHT };


    /* Keep level inside world area */

    if(delta.x < -pos.x)
        delta.x = -pos.x;
    if(delta.y < -pos.y)
        delta.y = -pos.y;

    if(delta.x > wsize.x - pos.x - lsize.x)
        delta.x = wsize.x - pos.x - lsize.x;
    if(delta.y > wsize.y - pos.y - lsize.y)
        delta.y = wsize.y - pos.y - lsize.y;


    // Note Level overlapping by itself could be a great mechanic, but for another game.

    /* Prevent level overlapping (horizontal) */

    for(auto const& other : world.levels)
    {
        auto const& opos = other.pos;

        if(pos.y > opos.y + lsize.y + abs(delta.y))
            continue;
        if(pos.y + lsize.y < opos.y - abs(delta.y))
            continue;

        if(pos.x + lsize.x + delta.x > opos.x)
        if(pos.x + delta.x < opos.x + lsize.x)
        {
            if(delta.x > 0 && pos.x + lsize.x <= opos.x)
                delta.x = opos.x - pos.x - lsize.x;

            if(delta.x < 0 && pos.x >= opos.x + lsize.x)
                delta.x = opos.x + lsize.x - pos.x;
        }
    }

    /* Prevent level overlapping (vertical) */

    for(auto const& other : world.levels)
    {
        auto const& opos = other.pos;

        if(pos.x > opos.x + lsize.x + abs(delta.x))
            continue;
        if(pos.x + lsize.x < opos.x - abs(delta.x))
            continue;

        if(pos.y + lsize.y + delta.y > opos.y)
        if(pos.y + delta.y < opos.y + lsize.y)
        {
            if(delta.y > 0 && pos.y + lsize.y <= opos.y)
                delta.y = opos.y - pos.y - lsize.y;

            if(delta.y < 0 && pos.y >= opos.y + lsize.y)
                delta.y = opos.y + lsize.y - pos.y;
        }
    }


    // TODO snap based on level structure, if any
    // I should only check the common walls where a level is touching another level.


    pos.x += delta.x;
    pos.y += delta.y;
}
