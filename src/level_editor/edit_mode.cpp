#include "level_editor/data.hpp"
#include "world/render.hpp"

using std::min;
using std::max;


bool LE::start_modifying_tiles(Point cursor)
{
    Point pos = get_level_coordinates(cursor);

    const bool ignore_scalable_constraints = true;
    auto pick = world::camera_pick_tile(*level(), pos, ignore_scalable_constraints);

    if(!pick.tile) // Create new
    {
        creating_tile = true;
        drag_start = pos;
        level()->tiles.push_back(world::Tile {
            .area = {
                (pos.x / 16) * 16,
                (pos.y / 16) * 16,
                16, 16
            },
            .mandatory_area = {0, 0, 16, 16} // I don't really want to let a block be zeroed out.
        });
        drag_target.tile = &(level()->tiles.back());
        return true;
    }
    else // Drag existing
    {

    }

    return false;
}

void LE::stop_modifying_tiles(Point cursor)
{
    if(creating_tile)
    {
        drag_target.tile = nullptr;
        creating_tile = false;
        return;
    }
}


void LE::drag_tiles(Point cursor, Point rel)
{
    Point pos = get_level_coordinates(cursor);

    if(creating_tile)
    {
        Rect area {
            min(drag_start.x, pos.x),
            min(drag_start.y, pos.y),
            max(drag_start.x, pos.x),
            max(drag_start.y, pos.y)
        };
        area.x = (area.x / 16) * 16;
        area.y = (area.y / 16) * 16;

        area.w = ((area.w - 1) / 16 + 1) * 16;
        area.h = ((area.h - 1) / 16 + 1) * 16;
        area.w -= area.x;
        area.h -= area.y;

        auto& tile = *drag_target.tile;
        tile.area = area;
        tile.original_area = area;
    }
}

