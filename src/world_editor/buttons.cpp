#include "world_editor/data.hpp"
#include <iostream>

using std::cout;
using std::endl;

WE::Button* WE::button_on_pos(Point pos)
{
    for(Button& btn : global_buttons)
    {
        Rect area {
            btn.pos.x + (btn.pos.x < 0) * (WINDOW_WIDTH - button_size.x),
            btn.pos.y + (btn.pos.y < 0) * (WINDOW_HEIGHT - button_size.y),
            button_size.x, button_size.y
        };

        if(SDL_PointInRect(&pos, &area))
            return &btn;
    }

    if(mouse_focus.selected)
    for(Button& btn : level_buttons)
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

        if(SDL_PointInRect(&pos, &area))
            return &btn;
    }

    return nullptr;
}

bool WE::click_button(Point pos)
{
    auto btn = button_on_pos(pos);

    if(btn)
    {
        if(btn->action)
            btn->action();
        return true;
    }

    return false;
}


