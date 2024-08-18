#include "game/game.hpp"
#include "core/core.hpp"
#include "game/render.hpp"
#include "game/player.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;
using std::min;

static auto& rnd = core::renderer;


void game::render_players(vector<Player> const& players)
{
    render_players(players.cbegin(), players.cend());
}

void game::render_players(vector<Player>::const_iterator begin, vector<Player>::const_iterator end)
{
    while(begin != end)
    {
        SDL_SetRenderDrawColor(rnd, 0, 128, 255, 255);
        SDL_RenderFillRectF(rnd, &(begin->area));

        begin++;
    }
}


// As the player isn't supposed to click on himself (yet), I won't be implementing margins here.
int game::camera_pick_player_idx(vector<Player> const& players, Point pos)
{
    for(int i = 0; i < (int) players.size(); i++)
    {
        auto const& area = players[i].area;

        if(area.x <= pos.x)
        if(area.y <= pos.y)
        if(area.x + area.w > pos.x)
        if(area.y + area.h > pos.y)
        {
            return i;
        }
    }
    return -1;
}

game::Player* game::camera_pick_player(vector<Player>& players, Point pos)
{
    int player = camera_pick_player_idx(players, pos);
    if(player == -1)
        return nullptr;

    return &(players[player]);
}
