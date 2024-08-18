#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world/render.hpp"
#include "world_editor/data.hpp"
#include "game/fonts.hpp"
#include "utils/textures.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

static auto& rnd = core::renderer;


void WE::render_level_tool_overlay()
{
    for(auto& btn : level_buttons)
        render_level_button(btn);
}
