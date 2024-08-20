#include "world/world.hpp"
#include <cmath>
#include <set>
#include <algorithm>

using std::abs;
using std::set;


bool world::is_world_playable(World const& world, string* msg)
{
    const string start_point = "game_start_point";

    int i = 0;

    for(auto const& data : world.levels)
    {
        auto const& objects = data.level.objects;
        for(auto const& obj : objects)
            if(obj.name == start_point)
                i++;
    }

    if(i == 1)
        return true;

    if(msg)
    {
        if(i == 0)
            *msg = "No '" + start_point + "' object found.";
        else
            *msg = "Multiple '" + start_point + "' objects found.";
    }

    return false;
}


bool world::is_level_playable(Level const& level, string* msg)
{
    const string start_point = "game_start_point";
    const string entry_point = "level_spawn_point";

    for(auto const& obj : level.objects)
    {
        if(obj.name == start_point || obj.name == entry_point)
            return true;
    }

    if(msg)
        *msg = "No suitable start point found.";

    return false;
}

bool world::is_level_reachable(World const& world, size_t index, vector<size_t>* ignore)
{
    const string start_point = "game_start_point";
    const string entry_point = "level_spawn_point";

    auto const& level = world.levels[index].level;

    bool can_enter = false;

    for(auto const& obj : level.objects)
    {
        if(obj.name == start_point)
            return true;
        if(obj.name == entry_point)
            can_enter = true;
    }
    if(!can_enter)
        return false;


    vector<size_t> _ignore;
    if(!ignore)
        ignore = &_ignore; // Use a temp one

    vector<size_t> neighbours = get_level_neighbours(world, index);
    for(size_t next : neighbours)
    {
        auto ign = std::find(ignore->begin(), ignore->end(), next);
        if(ign != ignore->end())
            continue;

        ignore->push_back(next);
        if(is_level_reachable(world, next, ignore))
            return true;
    }

    return false;
}

vector<size_t> world::get_level_neighbours(World const& world, size_t index)
{
    vector<size_t> neighbours;

    const Point size { WINDOW_WIDTH, WINDOW_HEIGHT };

    auto const& self = world.levels[index];
    Rect self_area {
        self.pos.x, self.pos.y,
        size.x + self.pos.x,
        size.y + self.pos.y
    };

    constexpr int min_td = min_touch_distance;

    for(size_t i = 0; i <  world.levels.size(); ++i)
    {
        auto const& data = world.levels[i];

        if(&data == &self)
            continue;

        Rect other_area {
            data.pos.x, data.pos.y,
            size.x + data.pos.x,
            size.y + data.pos.y
        };

        if(self_area.x == other_area.w && abs(self_area.y - other_area.y) < size.y - min_td)
            if(is_level_playable(data.level))
                neighbours.push_back(i);

        if(self_area.w == other_area.x && abs(self_area.y - other_area.y) < size.y - min_td)
            if(is_level_playable(data.level))
                neighbours.push_back(i);

        if(self_area.y == other_area.h && abs(self_area.x - other_area.x) < size.x - min_td)
            if(is_level_playable(data.level))
                neighbours.push_back(i);

        if(self_area.h == other_area.y && abs(self_area.x - other_area.x) < size.x - min_td)
            if(is_level_playable(data.level))
                neighbours.push_back(i);
    }

    return neighbours;
}


void world::world_update_reach_map(World& world)
{
    for(size_t i = 0; i < world.levels.size(); ++i)
        world.levels[i].reachable = is_level_reachable(world, i);
}
