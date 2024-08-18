#include "core/scene.hpp"

#include "startup/startup.hpp"
#include "game/game.hpp"
#include "world/scene.hpp"
#include "level_editor/level_editor.hpp"
#include "world_editor/world_editor.hpp"


void core::register_scenes()
{
    core::scene<game::scene_uid>(); // Only meant for mechanic prototyping; currently not working
    core::scene<world::scene_uid>();

    core::scene<startup::scene_uid>("startup");
    //core::scene<menu::scene_uid>("menu"); // TODO add

    core::scene<LE::scene_uid>("level_editor");
    core::scene<WE::scene_uid>("world_editor");

    core::set_scene("world_editor");
    //core::set_scene("startup");
}


