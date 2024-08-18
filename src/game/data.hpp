#ifndef INCLUDE_GAME_DATA_HPP
#define INCLUDE_GAME_DATA_HPP

#include "game/player.hpp"
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

    void update_collisions(u32 ms, Level&, vector<Player>& players);
    void apply_tile_constraints(Level&);
    void apply_player_player_collisions(Player&);
    void apply_player_tile_collisions(u32 ms, Level&, Player&);
}

#endif // INCLUDE_GAME_DATA_HPP
