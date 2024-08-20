#include "level_editor/data.hpp"
#include "core/scene.hpp"
#include "game/data.hpp"
#include <iostream>

using std::endl;
using std::cout;


void LE::play_level()
{
    string message; // TODO show to user
    if(!world::is_level_playable(*(level()), &message))
    {
        cout << message << endl;
        last_action_error = message;
        return;
    }

    game::load_level(target_level);
    core::set_scene("game");
    game::enable_level_editor = true;
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
    menu_scroll = 0;
    mode = OBJECT_MODE;
}

void LE::set_texture_mode()
{
    menu_scroll = 0;
    mode = TEXTURE_MODE;
}


void LE::open_world_editor()
{
    active_players = 0;
    core::set_scene("world_editor");
}
