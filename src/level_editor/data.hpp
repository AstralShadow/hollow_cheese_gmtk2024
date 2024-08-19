#ifndef INCLUDE_LE_DATA_HPP
#define INCLUDE_LE_DATA_HPP

#include "utils/types.hpp"
#include "world/data.hpp"
#include "game/player.hpp"
//#include "world_editor/data.hpp"

namespace LE
{
    using world::Level;

    extern int target_level;
    Level* level();


    struct PlayerData
    {
        bool display_jump_reach = false;
        bool dragging = false;
    };

    using game::Player;
    extern vector<Player> players; // Mock player objects
    extern vector<PlayerData> player_data;
    extern int active_players;

    extern bool simulate_game;



    enum mode_t
    {
        EDIT_MODE,
        BACKGROUND_MODE,
        FOREGROUND_MODE
    } extern mode;


    /* Rendering */

    void render_levels(); // Rendered at 80% from screen
    Point get_level_coordinates(Point screen_pos);

    void render_player_overlays(); // jump reach

    // May use Level to add snap hints.. tho not yet
    void render_grid(Level const&, float scale = 1);


    /* Actions */

    void toggle_game_simulation();
}

#endif // INCLUDE_LE_DATA_HPP
