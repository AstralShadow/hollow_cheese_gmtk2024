#include "level_editor/data.hpp"
#include "core/scene.hpp"


void LE::play_level()
{
    string message;
    if(!world::is_playable_world(world::world, message))
    {
        cout << message << endl;
        return;
    }

    core::set_scene("game");
    world::world.current_level = target_level;
    world::reset_level(*level());
}

void LE::toggle_slow_motion()
{
    slow_motion = !slow_motion;
}

void LE::toggle_time_pause()
{
    time_pause = !time_pause;
}

void LE::toggle_jump_prediction()
{
    jump_prediction = (jump_prediction + 1) % 3;
}


void LE::set_edit_mode()
{
    mode = EDIT_MODE;
}

void LE::set_object_mode()
{
    //mode = OBJECT_MODE;
}

void LE::set_texture_mode()
{
    //mode = TEXTURE_MODE;
}


void LE::open_world_editor()
{
    active_players = 0;
    core::set_scene("world_editor");
}
