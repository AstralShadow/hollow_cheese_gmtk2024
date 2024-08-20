#include "game/game.hpp"
#include "game/data.hpp"
#include "core/core.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::tick(u32 ms, scene_uid)
{
    if(ms > 20)
    {
        cout << "Capping deltaTime: " << ms << "-> 20" << endl;
        ms = 20;
    }

    using world::world;

    if(world.current_level >= world.levels.size())
        core::set_scene("world_editor");

    tick_players(ms, players);

    update_collisions(ms, world.levels[world.current_level].level, players);
}
