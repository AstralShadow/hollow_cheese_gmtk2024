#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include "game/data.hpp"


namespace LE
{
    int target_level = 0;
    mode_t mode = EDIT_MODE;

    vector<Player> players;
    vector<PlayerData> players_data;
    int active_players = 2;

    bool simulate_game = !true;

    bool creating_tile = false;
    Point drag_start;
    Point drag_buffer;
    bool modifying_tile_scalable_sides;
    bool removing_tiles = false;

    vector<Button> buttons, mode_buttons;
}

world::Level* LE::level()
{
    if(target_level > -1 && (size_t) target_level < world::world.levels.size())
        return &(world::world.levels[target_level].level);
    return nullptr;
}



void LE::init(int, char**, scene_uid)
{
    players = game::players; // Copy players
    for(size_t i = 0; i < players.size(); ++i)
        players_data.emplace_back();

    Rect scene_area {
        32, 48,
        static_cast<int>(WINDOW_WIDTH * 0.8),
        static_cast<int>(WINDOW_HEIGHT * 0.8)
    };

    buttons.emplace_back(Point{32 + 4, 8},
                         "Simulation (toggle)", &toggle_game_simulation);

    mode_buttons.emplace_back(Point{scene_area.x + scene_area.w - 4 - button_size.x, 8},
                              "Edit mode", &set_edit_mode);

    for(auto& btn : buttons)
        generate_button_label(btn);
    for(auto& btn : mode_buttons)
        generate_button_label(btn);
}

void LE::deinit(scene_uid)
{

}
