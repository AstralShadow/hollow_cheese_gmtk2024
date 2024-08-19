#ifndef INCLUDE_LE_DATA_HPP
#define INCLUDE_LE_DATA_HPP

#include "utils/types.hpp"
#include "world/data.hpp"
#include "game/player.hpp"
//#include "world_editor/data.hpp"

namespace LE
{
    extern int target_level;

    world::Level* level();

    struct PlayerData
    {
        bool display_jump_reach = false;
        bool dragging = false;
    };

    using game::Player;
    extern vector<Player> players; // Mock player objects
    extern vector<PlayerData> player_data;
    extern int active_players;

    void render_player_overlays(); // jump reach


    enum mode_t
    {
        EDIT_MODE,
        BACKGROUND_MODE,
        FOREGROUND_MODE
    } extern mode;

    extern bool simulate_game;

    void render_levels(); // Rendered at 80% from screen


    void toggle_game_simulation();
}

#endif // INCLUDE_LE_DATA_HPP
