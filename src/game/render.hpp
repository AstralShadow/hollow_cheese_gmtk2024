#ifndef INCLUDE_GAME_RENDER_HPP
#define INCLUDE_GAME_RENDER_HPP

#include "game/player.hpp"
#include <vector>

using std::vector;


namespace game
{
    void render_players(vector<Player> const&);
    void render_players(vector<Player>::const_iterator begin, vector<Player>::const_iterator end);

    int camera_pick_player_idx(vector<Player> const&, Point pos);
    Player* camera_pick_player(vector<Player>&, Point pos);
}

#endif // INCLUDE_GAME_RENDER_HPP
