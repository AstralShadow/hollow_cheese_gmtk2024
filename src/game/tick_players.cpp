#include "game/game.hpp"
#include "game/player.hpp"


void game::tick_players(u32 ms, vector<Player>& players)
{
    for(auto& player : players)
        move_player(ms, player);
}
