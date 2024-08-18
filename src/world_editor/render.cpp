#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world/render.hpp"
#include "world_editor/data.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void WE::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    {
        size_t temp = world::world.current_level;

        world::world.current_level = mouse_focus.level;
        world::render_world(world::world, true);

        world::world.current_level = temp;
    }

    if(mouse_focus.selected)
        render_level_tool_overlay();

    for(auto& btn : global_buttons)
        render_global_button(btn);

    // TODO add revisions and level names

    SDL_RenderPresent(rnd);
}
