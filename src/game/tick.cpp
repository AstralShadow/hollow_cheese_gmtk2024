#include "game/game.hpp"
#include "game/data.hpp"


void game::tick(u32 ms, scene_uid)
{
    tick_players(ms, players);
}
