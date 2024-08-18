#include "game/game.hpp"
#include "game/player.hpp"


void game::tick_players(u32 ms, vector<Player>& players)
{
    tick_players(ms, players.begin(), players.end());
}

void game::tick_players(u32 ms, vector<Player>::iterator begin, vector<Player>::iterator end)
{
    while(begin != end)
        move_player(ms, *(begin++));
}
