#include "level_editor/level_editor.hpp"
#include "core/core.hpp"
#include "world/render.hpp"
#include "level_editor/data.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void LE::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    world::render_level(*(level()));

    // TODO render UI

    SDL_RenderPresent(rnd);
}
