#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world/render.hpp"
#include "world/data.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void WE::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);

    // TODO render UI
    // TODO render world map

    world::render_world(world::world, !true);

    // TODO render world map overlay


    SDL_RenderPresent(rnd);
}
