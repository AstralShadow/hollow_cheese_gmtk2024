#include "core/scene.hpp"

#include "startup/startup.hpp"
#include "game/game.hpp"


void core::register_scenes()
{
    core::scene<startup::scene_uid>("startup");
    core::scene<game::scene_uid>("game"); // Only meant for prototyping

    core::set_scene("game");
}


