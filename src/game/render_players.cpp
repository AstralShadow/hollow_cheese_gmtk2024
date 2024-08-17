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
    for(auto const& player : players)
    {
        SDL_SetRenderDrawColor(rnd, 0, 128, 255, 255);
        SDL_RenderFillRectF(rnd, &player.area);
    }
}

// As the player isn't supposed to click on himself (yet), I won't be implementing margins here.
game::Player* game::camera_pick_player(vector<Player>& players, Point pos)
{
    for(auto& player : players)
    {
        auto const& area = player.area;

        if(area.x <= pos.x)
        if(area.y <= pos.y)
        if(area.x + area.w > pos.x)
        if(area.y + area.h > pos.y)
        {
            return &player;
        }
    }
    return nullptr;
}
