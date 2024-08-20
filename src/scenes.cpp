#include "core/scene.hpp"

#include "startup/startup.hpp"
#include "game/game.hpp"
#include "world/scene.hpp"
#include "level_editor/level_editor.hpp"
#include "world_editor/world_editor.hpp"

#include "world/world.hpp"
#include "world_editor/data.hpp"


void core::register_scenes()
{
    core::scene<world::scene_uid>(); // stores data

    core::scene<startup::scene_uid>("startup");
    //core::scene<menu::scene_uid>("menu"); // TODO add
    core::scene<game::scene_uid>("game");

    core::scene<LE::scene_uid>("level_editor");
    core::scene<WE::scene_uid>("world_editor");


#ifndef __EMSCRIPTEN__
    if(world::world.levels.empty())
        WE::new_level();
#endif
    core::set_scene("level_editor");
    //core::set_scene("world_editor");

#ifdef __EMSCRIPTEN__
    core::set_scene("startup");
#endif
}


