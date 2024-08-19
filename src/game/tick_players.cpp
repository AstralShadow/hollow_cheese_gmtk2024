#include "game/game.hpp"
#include "game/player.hpp"


void game::tick_players(u32 ms, vector<Player>& players)
{
    tick_players(ms, players.begin(), players.end());
}

void game::tick_players(u32 ms, vector<Player>::iterator begin, vector<Player>::iterator end)
{
    while(begin != end)
        tick_player(ms, *(begin++));
}

void game::tick_player(u32 ms, Player& player, bool artifical_motion)
{
    move_player(ms, player, artifical_motion);
}
