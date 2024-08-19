#include "level_editor/data.hpp"


void LE::toggle_game_simulation()
{
    simulate_game = !simulate_game;
}

void LE::toggle_slow_motion()
{
    // TODO toggle slow motion
}

void LE::toggle_time_pause()
{
    // TODO toggle time pause
}


static void reset_mode_button_focus()
{
    for(auto& btn : LE::mode_buttons)
        btn.focused = false;
}

void LE::set_edit_mode()
{
    mode = EDIT_MODE;
    reset_mode_button_focus();
}
