#include "world/data.hpp"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::abs;


static bool is_valid(Point pos, world::World const& world)
{
    for(auto const& data : world.levels)
    {
        auto const& opos = data.pos;
        if(pos.x < opos.x + WINDOW_WIDTH)
        if(pos.y < opos.y + WINDOW_HEIGHT)
        if(opos.x < pos.x + WINDOW_WIDTH)
        if(opos.y < pos.y + WINDOW_HEIGHT)
            return false;
    }

    return true;
}

Point world::find_empty_level_pos(int close_to)
{
    const Point target = close_to != -1 ? world.levels[close_to].pos : Point{0, 0};

    bool first = true;
    int distance = 0;
    Point pos {-1, -1}; // invalid position

    for(int x = 0; x < world.size.x / WINDOW_WIDTH; x++)
    for(int y = 0; y < world.size.y / WINDOW_HEIGHT; y++)
    {
        Point _pos {
            x * WINDOW_WIDTH,
            y * WINDOW_HEIGHT
        };
        if(!is_valid(_pos, world))
            continue;

        if(close_to == -1)
            return _pos;

        int _distance = abs(_pos.x - target.x) + abs(_pos.y - target.y);
        if(first || _distance < distance) {
            pos = _pos;
            distance = _distance;
            first = false;
        }
    }

    return pos;
}
