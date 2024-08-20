#include "game/game.hpp"
#include "core/core.hpp"
#include "game/data.hpp"
#include "game/render.hpp"
#include "world/render.hpp"
#include "game/button.hpp"
#include <SDL2/SDL_render.h>
#include <stdexcept>

static auto& rnd = core::renderer;


void game::render(scene_uid)
{
    using world::world;

    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    world::render_level(world.levels[world.current_level].level);
    render_players(players);

    if(game::enable_level_editor)
    {
        render_button(level_editor_btn, level_editor_btn.pos);
        if(level_editor_btn.focused)
        {
            auto label_area = level_editor_btn.label_size;
            render_button_label(level_editor_btn,
                                level_editor_btn.pos + Point{40, 16 - label_area.y / 2});
        }
    }

    SDL_RenderPresent(rnd);
}
