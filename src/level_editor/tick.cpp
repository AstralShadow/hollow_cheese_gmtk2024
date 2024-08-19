#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include "core/scene.hpp"
#include "game/data.hpp" // collisions
#include <iostream>

using std::cout;
using std::endl;


void LE::tick(u32 ms, scene_uid)
{
    if(!level()) // fall back to WE
        core::set_scene("world_editor");

    if(simulate_game && !time_pause)
    for(int i = 0; i < active_players; i++)
    {
        if(players_data[i].dragging)
            continue; // Skip players who are being dragged around

        u32 _ms = slow_motion ? 0 : ms;

        if(slow_motion) {
            static u32 bank = 0;
            bank += ms;
            if(bank > slow_motion_factor) {
                _ms = bank / slow_motion_factor;
                bank = bank % slow_motion_factor;
            }
        }

        if(ms > 0)
        {
            auto itr = players.begin() + i;
            tick_players(_ms, itr, itr + 1);
            update_collisions(_ms, *level(), itr, itr + 1);
        }
    }
}
