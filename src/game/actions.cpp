#include "game/data.hpp"
#include "world/data.hpp"
#include "core/core.hpp"
#include "level_editor/data.hpp"


void game::open_level_editor()
{
    world::reset_level(world::world.levels[world::world.current_level].level);

    LE::target_level = world::world.current_level;
    core::set_scene("level_editor");
}
