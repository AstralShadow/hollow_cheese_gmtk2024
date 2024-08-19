#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include "game/data.hpp"


namespace LE
{
    int target_level = 0;
    mode_t mode = EDIT_MODE;

    vector<Player> players;
    vector<PlayerData> players_data;
    int active_players = 0;
#ifdef __EMSCRIPTEN__
    int jump_prediction = 0;
#else
    int jump_prediction = 2;
#endif

#ifdef __EMSCRIPTEN__
    bool simulate_game = false;
#else
    bool simulate_game = true;
#endif
    bool time_pause = false;
    bool slow_motion = false;

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


    // TODO add keyboard shortcuts too
    // TODO move text constants in header to not desync with render_buttons

    buttons.emplace_back(Point{32 + 4, 8},
                         "Simulation (toggle)", &toggle_game_simulation, "simulation");
    buttons.emplace_back(Point{(32 + 4) * 2, 8},
                         "Player count (toggle)", (void(*)()) &toggle_player_count, "player_count");
    buttons.emplace_back(Point{(32 + 4) * 3, 8},
                         "Jump prediction (toggle)", &toggle_jump_prediction, "jump_prediction");

    buttons.emplace_back(Point{(32 + 4) * 5, 8},
                         "Time pause (toggle)", &toggle_time_pause, "time_pause");
    buttons.emplace_back(Point{(32 + 4) * 6, 8},
                         "Slow motion (toggle)", &toggle_slow_motion, "slow_motion");


    mode_buttons.emplace_back(Point{scene_area.x + scene_area.w - (4 + button_size.x), 8},
                              "Back to world editor", &open_world_editor, "exit");

    mode_buttons.emplace_back(Point{scene_area.x + scene_area.w - (4 + button_size.x) * 5, 8},
                              "Edit mode", &set_edit_mode, "edit_mode");

    mode_buttons.emplace_back(Point{scene_area.x + scene_area.w - (4 + button_size.x) * 6, 8},
                              "Object mode", &set_object_mode, "object_mode");

    mode_buttons.emplace_back(Point{scene_area.x + scene_area.w - (4 + button_size.x) * 7, 8},
                              "Texture mode", &set_texture_mode, "texture_mode");

    for(auto& btn : buttons)
        generate_button_label(btn);
    for(auto& btn : mode_buttons)
        generate_button_label(btn);
}

void LE::deinit(scene_uid)
{

}
