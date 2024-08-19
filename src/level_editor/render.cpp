#include "level_editor/level_editor.hpp"
#include "core/core.hpp"
#include "world/render.hpp"
#include "level_editor/data.hpp"
#include "game/render.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

static auto& rnd = core::renderer;


void LE::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_levels();

    switch(mode)
    {
    case EDIT_MODE:
        //render_edit_ui();
        //render_edit_overlay();
        break;
    case BACKGROUND_MODE:
        break;
    case FOREGROUND_MODE:
        break;
    }

    // TODO render UI

    SDL_RenderPresent(rnd);
}


void LE::render_levels()
{
    SDL_Rect area {
        32,
        48,
        static_cast<int>(WINDOW_WIDTH * 0.8),
        static_cast<int>(WINDOW_HEIGHT * 0.8)
    };

    SDL_RenderSetViewport(rnd, &area);

    world::render_level(*(level()), 0.8);

    if(simulate_game)
    {
        SDL_RenderSetScale(rnd, 0.8, 0.8);
        game::render_players(players.begin(), players.end() + active_players);
        render_player_overlays();
        SDL_RenderSetScale(rnd, 1, 1);
    }

    SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    SDL_RenderDrawRect(rnd, nullptr);


    const Point level_size = { WINDOW_WIDTH, WINDOW_HEIGHT };
    Point level_pos = world::world.levels[target_level].pos;
    Rect screen {
        level_pos.x - level_size.x / 8,
        level_pos.y - level_size.y / 8,
        static_cast<int>(level_size.x * 1.25),
        static_cast<int>(level_size.y * 1.25)
    };

    for(auto const& data : world::world.levels)
    {
        auto const& pos = data.pos;
        if(pos.x <= screen.x + screen.w)
        if(pos.y <= screen.y + screen.h)
        if(pos.x + level_size.x > screen.x)
        if(pos.y + level_size.y > screen.y)
        if(&data.level != level())
        {
            SDL_Rect area2 {
                static_cast<int>((pos.x - level_pos.x) * 0.8) + area.x,
                static_cast<int>((pos.y - level_pos.y) * 0.8) + area.y,
                area.w,
                area.h
            };
            SDL_RenderSetViewport(rnd, &area2);

            world::render_level(*(level()), 0.8);

            SDL_SetRenderDrawColor(rnd, 0, 0, 0, 96);
            SDL_RenderFillRect(rnd, nullptr);
        }
    }

    SDL_RenderSetViewport(rnd, nullptr);
}

void LE::render_player_overlays()
{
    game::render_players_jump_reach(*level(), players.begin(), players.end() + active_players);
}
