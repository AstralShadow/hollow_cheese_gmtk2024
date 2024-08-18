#ifndef INCLUDE_GAME_RENDER_HPP
#define INCLUDE_GAME_RENDER_HPP

#include "game/player.hpp"
#include <vector>

using std::vector;


namespace game
{
    void render_players(vector<Player> const&);
    Player* camera_pick_player(vector<Player>&, Point pos);
}

#endif // INCLUDE_GAME_RENDER_HPP
