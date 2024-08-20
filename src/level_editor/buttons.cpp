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


LE::MenuZone* LE::zone_on_pos(Point pos)
{
    if(mode == OBJECT_MODE || mode == TEXTURE_MODE)
    if(menu_zones.size() > 0)
    {
        for(auto& zone : menu_zones)
        {
            Rect area = zone.area;

            if(SDL_PointInRect(&pos, &area))
                return &zone;
        }
    }

    return nullptr;
}

bool LE::click_zone(Point pos)
{
    auto zone = zone_on_pos(pos);
    if(!zone)
        return false;

    switch(mode)
    {
    case EDIT_MODE:
        return false;

    case OBJECT_MODE:
        return click_zone_object_mode(zone->index);

    case TEXTURE_MODE:
        return click_zone_texture_mode(zone->index);
    }

    return false;
}
