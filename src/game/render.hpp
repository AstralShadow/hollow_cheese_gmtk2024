#ifndef INCLUDE_GAME_RENDER_HPP
#define INCLUDE_GAME_RENDER_HPP

#include "game/player.hpp"
#include "world/level.hpp"
#include <vector>

using std::vector;


namespace game
{
    void render_players(vector<Player> const&);
    void render_players(vector<Player>::const_iterator begin, vector<Player>::const_iterator end);

    int camera_pick_player_idx(vector<Player> const&, Point pos);
    Player* camera_pick_player(vector<Player>&, Point pos);

    void render_players_jump_reach(world::Level const& scene, vector<Player> const&);
    void render_players_jump_reach(world::Level const& scene, vector<Player>::const_iterator begin,
                                                              vector<Player>::const_iterator end);
}

#endif // INCLUDE_GAME_RENDER_HPP
