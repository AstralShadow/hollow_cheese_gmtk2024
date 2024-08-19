#include "level_editor/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


LE::Button* LE::button_on_pos(Point pos)
{
    for(Button& btn : buttons)
    {
        Rect area {
            btn.pos.x, btn.pos.y,
            button_size.x, button_size.y
        };

        if(SDL_PointInRect(&pos, &area))
            return &btn;
    }

    for(Button& btn : mode_buttons)
    {
        Rect area {
            btn.pos.x, btn.pos.y,
            button_size.x, button_size.y
        };

        if(SDL_PointInRect(&pos, &area))
            return &btn;
    }

    return nullptr;
}

bool LE::click_button(Point pos)
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

