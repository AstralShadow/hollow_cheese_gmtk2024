#include "game/game.hpp"
#include "core/core.hpp"
#include "game/render.hpp"
#include "game/player.hpp"
#include "game/data.hpp"
#include <SDL2/SDL_render.h>
#include <cmath>
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



static void progress_player(u32 ms, game::Player&, world::Level const&);

void game::render_players_jump_reach(world::Level const& scene, vector<Player> const& players)
{
    render_players_jump_reach(scene, players.cbegin(), players.cend());
}

void game::render_players_jump_reach(world::Level const& scene,
                                     vector<Player>::const_iterator begin,
                                     vector<Player>::const_iterator end)
{
    // TODO accept scale argument to not need SDL-based one. This will make rects look better.
    while(begin != end)
    {
        Player clone = *(begin++);
        clone.area_past = clone.area;

        if(clone.has_foothold) { // Simulate jump
            clone.velocity.y = -clone.jump_force;
            clone.has_foothold = false;
        }


        SDL_SetRenderDrawColor(rnd, 0, 128, 255, 32);
        const u32 step = 11; // ms; Hand picked so that the character doesn't glitch trough blocks

        /* Left jump */ {
            auto left = clone;

            left.velocity.x = -1;

            while(!left.has_foothold) // simulate some game ticks
            {
                progress_player(step, left, scene);

                auto& area = left.area;
                SDL_RenderDrawRectF(rnd, &area);

                // Stop if out of screen
                if(area.x + area.w < 0)
                    break;
                if(area.x > WINDOW_WIDTH)
                    break;
                if(area.y > WINDOW_HEIGHT)
                    break;

                // stop if stuck (for some reason?)
                if(left.area_past == left.area)
                    break;

                left.area_past = left.area; // update for next simulation step
            }
            SDL_RenderFillRectF(rnd, &left.area);
        }

        /* Right jump */ {
            auto right = clone;

            right.velocity.x = 1;

            while(!right.has_foothold) // simulate some game ticks
            {
                progress_player(step, right, scene);

                auto& area = right.area;
                SDL_RenderDrawRectF(rnd, &area);

                // Stop if out of screen
                if(area.x + area.w < 0)
                    break;
                if(area.x > WINDOW_WIDTH)
                    break;
                if(area.y > WINDOW_HEIGHT)
                    break;

                // stop if has foothold
                if(right.has_foothold)
                    break;

                // stop if stuck (for some reason?)
                if(right.area_past == right.area)
                    break;

                right.area_past = right.area; // update for next simulation step
            }
            SDL_RenderFillRectF(rnd, &right.area);
        }
    }
}

void progress_player(u32 ms, game::Player& clone, world::Level const& stage)
{
    game::tick_player(ms, clone, true);
    game::apply_player_tile_collisions_lvlnoop(ms, stage, clone);
}
