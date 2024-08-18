#ifndef INCLUDE_GAME_DATA_HPP
#define INCLUDE_GAME_DATA_HPP

#include "game/player.hpp"
#include "world/data.hpp"
#include <vector>

using std::vector;


namespace game
{
    using world::Map;
    using world::Tile;
    using world::PickedTile;

    extern vector<Player> players;

    void update_collisions(u32 ms, Map&, vector<Player>& players);
    void apply_tile_constraints(Map&);
    void apply_player_player_collisions(Player&);
    void apply_player_tile_collisions(u32 ms, Map&, Player&);
}

#endif // INCLUDE_GAME_DATA_HPP
