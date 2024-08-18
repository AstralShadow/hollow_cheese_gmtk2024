#include "world/world.hpp"


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

    // TODO prevent collisions
    // TODO snap based on level structure, if any

    // stub
    pos.x += delta.x;
    pos.y += delta.y;
}
