#include "game/game.hpp"
#include "game/data.hpp"
#include "core/core.hpp"
#include <stdexcept>


void game::tick(u32 ms, scene_uid)
{
    using world::world;

    if(world.current_level >= world.levels.size())
        core::set_scene("world_editor");

    tick_players(ms, players);

    update_collisions(ms, world.levels[world.current_level].level, players);
}
