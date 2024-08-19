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

    vector<Button> buttons;
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

    //level_buttons.emplace_back(Point{-4, 4}, "Clone", &clone_level);

    //buttons.emplace_back(Point{-4, 4}, "", &clone_level);

    //for(auto& btn : buttons)
    //    generate_button_label(btn);
}

void LE::deinit(scene_uid)
{

}
