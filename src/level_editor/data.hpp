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
        // bool keep_displaying_jump_reach = false;
        bool dragging = false;
        bool plan_to_drop = false; // Don't drop within collidable area
        Point drag_offset {0, 0};
    };

    using game::Player;
    extern vector<Player> players; // Mock player objects
    extern vector<PlayerData> players_data;
    extern int active_players; // I don't want to touch the vector above, it contains controllers

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

    void render_player_overlays(float scale); // Calls SDL_RenderSetScale internally

    // May use Level to add snap hints.. tho not yet
    void render_grid(Level const&, float scale = 1);


    /* Actions */

    void toggle_game_simulation();
}

#endif // INCLUDE_LE_DATA_HPP
