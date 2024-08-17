#include "game/game.hpp"
#include "game/data.hpp"


void game::tick(u32 ms, scene_uid)
{
    for(auto& player : players)
        tick_player(ms, player);
}
