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

    switch(tile.side)
    {
    case TOP:
        area.y += delta.y;
        area.h -= delta.y;
        break;

    case RIGHT:
        area.w += delta.x;
        break;

    case BOTTOM:
        area.h += delta.y;
        break;

    case LEFT:
        area.x += delta.x;
        area.w -= delta.x;
        break;
    }

    normalize_tile(*tile.tile);
}
