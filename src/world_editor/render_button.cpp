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


void WE::render_level_button(Button const& btn)
{
    Rect area {
        mouse_focus.area.x + (btn.pos.x >= 0) * (mouse_focus.area.w) + btn.pos.x,
        mouse_focus.area.y + (btn.pos.y < 0) * (mouse_focus.area.h) + btn.pos.y,
        button_size.x, button_size.y
    };
    if(btn.pos.x < 0)
        area.x -= area.w;
    if(btn.pos.y < 0)
        area.y -= area.h;

    render_button(btn, area);


    /* Render label */

    if(btn.focused)
    {
        Point label {
            area.x + (btn.pos.x > 0 ? area.w + 4 : -btn.label_size.x - 4),
            area.y + area.h / 2 - btn.label_size.y / 2,
        };

        render_button_label(btn, label);
    }
}

void WE::render_global_button(Button const& btn)
{
    Rect area {
        btn.pos.x + (btn.pos.x < 0) * (WINDOW_WIDTH - button_size.x),
        btn.pos.y + (btn.pos.y < 0) * (WINDOW_HEIGHT - button_size.y),
        button_size.x, button_size.y
    };

    render_button(btn, area);

    /* Render label */

    if(btn.focused)
    {
        Point label {
            area.x + (btn.pos.x > 0 ? button_size.x + 4 : -btn.label_size.x - 4),
            area.y + area.h / 2 - btn.label_size.y / 2
        };

        render_button_label(btn, label);
    }
}
