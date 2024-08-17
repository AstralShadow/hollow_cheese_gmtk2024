#include "game/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::normalize_tile(Tile& tile)
{
    Rect& area = tile.area;

    if(area.w < 0) {
        area.w *= -1;
        area.x -= area.w;
    }

    if(area.h < 0) {
        area.h *= -1;
        area.y -= area.h;
    }
}

void game::scale_tile(PickedTile tile, Point delta)
{
    if(!tile.tile)
        return;

    Rect& area = tile.tile->area;
    Point const& min_size = tile.tile->min_size;

    switch(tile.side)
    {
    case TOP:
        area.y += delta.y;
        area.h -= delta.y;
        if(area.h < min_size.y) {
            area.y -= min_size.y - area.h;
            area.h = min_size.y;
        }
        break;

    case RIGHT:
        area.w += delta.x;
        if(area.w < min_size.x)
            area.w = min_size.x;
        break;

    case BOTTOM:
        area.h += delta.y;
        if(area.h < min_size.y)
            area.h = min_size.y;
        break;

    case LEFT:
        area.x += delta.x;
        area.w -= delta.x;
        if(area.w < min_size.x) {
            area.x -= min_size.x - area.w;
            area.w = min_size.x;
        }
        break;
    }

    normalize_tile(*tile.tile);
}
