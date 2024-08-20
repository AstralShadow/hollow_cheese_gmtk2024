#ifndef INCLUDE_GAME_DATA_HPP
#define INCLUDE_GAME_DATA_HPP

#include "game/player.hpp"
#include "game/button.hpp"
#include "world/data.hpp"
#include <vector>

using std::vector;


namespace game
{
    using world::Tile;
    using world::Level;
    using world::PickedTile;
    using world::World;

    using world::world;

    extern vector<Player> players;

    extern bool enable_level_editor;
    extern Button level_editor_btn;

    void update_collisions(u32 ms, Level&, vector<Player>& players);
    void update_collisions(u32 ms, Level&, vector<Player>::iterator begin,
                                           vector<Player>::iterator end);
    void apply_tile_constraints(Level&);
    void apply_player_player_collisions(Player&);
    void apply_player_tile_collisions(u32 ms, Level&, Player&);
    void apply_player_tile_collisions_lvlnoop(u32 ms, Level const&, Player&);


    /* Actions */

    void open_level_editor(); // only if already visited


    // Utility

    void load_level(int index); // Load player positions from level data

    void pick_first_level();
    void position_players_near(string object, int prev_level = -1);
}

#endif // INCLUDE_GAME_DATA_HPP
