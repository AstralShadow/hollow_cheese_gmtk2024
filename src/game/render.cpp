#include "game/game.hpp"
#include "core/core.hpp"
#include "game/data.hpp"
#include "game/render.hpp"
#include "world/render.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void game::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    world::render_map(world::map);
    render_players(players);

    SDL_RenderPresent(rnd);

    //SDL_RenderSetViewport(rnd, nullptr);
}
