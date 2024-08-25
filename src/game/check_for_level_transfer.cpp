#include "game/data.hpp"
#include "world/data.hpp"

using namespace world;


void game::check_for_level_transfer()
{
    Point point;
    bool change = false;
    for(auto& p : players) {
        if(p.area.x + p.area.w < 0)
            change = true;
        if(p.area.y + p.area.h < 0)
            change = true;
        if(p.area.x > WINDOW_WIDTH)
            change = true;
        if(p.area.y > WINDOW_HEIGHT)
            change = true;

        if(change)
        {
            point = {
                static_cast<int>(p.area.x),
                static_cast<int>(p.area.y)
            };
            break;
        }
    }

    if(!change)
        return;

    // TODO plan animated transition

    size_t current = world::world.current_level;
    auto& data = world::world.levels[current];
    auto pos = data.pos + point;

    auto others = get_level_neighbours(world, current);
    bool first = true;
    int dist = 0;
    size_t next = current;
    for(auto o : others)
    {
        auto pos2 = world.levels[o].pos + Point{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
        auto d = pos2 - pos;
        auto dist2 = d.x * d.x + d.y * d.y;
        if(first || dist > dist2)
        {
            first = false;
            dist = dist2;
            next = o;
        }
    }

    if(next != current) {
        world.current_level = next;
        position_players_near("level_spawn_point", next);
    }
}
