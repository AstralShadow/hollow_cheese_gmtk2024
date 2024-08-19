#include "level_editor/data.hpp"
#include "world/render.hpp"
#include "game/data.hpp"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::min;
using std::max;


bool LE::start_modifying_tiles(Point cursor)
{
    Point pos = get_level_coordinates(cursor);

    if(pos.x < 0 || pos.y < 0)
        return false;
    if(pos.x > WINDOW_WIDTH || pos.y > WINDOW_HEIGHT)
        return false;

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
            .min_size = {16, 16} // I don't really want to let a block be zeroed out.
        });
        drag_target.tile = &(level()->tiles.back());
    }
    else // Resize existing tile
    {
        drag_start = pos;
        drag_buffer = {0, 0};
        if(pick.tile->original_area != pick.tile->area)
            throw std::runtime_error("You let the level editor resize a tile with state!\n"
                                     "You should reset your level before editing it.");
        drag_target = pick;
    }

    return true;
}

void LE::stop_modifying_tiles(Point cursor)
{
    if(creating_tile)
    {
        game::apply_tile_constraints(*(level()));

        auto& tile = *drag_target.tile;
        tile.original_area = tile.area;

        drag_target.tile = nullptr;
        creating_tile = false;
        return;
    }

    if(drag_target.tile) // Editing tile
    {
        game::apply_tile_constraints(*(level()));

        auto& tile = *drag_target.tile;
        tile.original_area = tile.area;

        drag_target.tile = nullptr;
        return;
    }
}


void LE::drag_tiles(Point cursor, Point)
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

        area.w = (area.w / 16) * 16 + (area.w % 16 ==  0 ? 0 : 16);
        area.h = (area.h / 16) * 16 + (area.w % 16 ==  0 ? 0 : 16);
        area.w -= area.x;
        area.h -= area.y;
        if(area.w < 16)
            area.w = 16;
        if(area.h < 16)
            area.h = 16;

        auto& tile = *drag_target.tile;
        tile.area = area;
        game::apply_tile_constraints(*(level()));
        tile.area_past = tile.area;
    }
    else if (drag_target.tile)
    {
        // Increment the buffer with level coordinates
        Point delta = pos - drag_start;
        drag_buffer = drag_buffer + delta;
        drag_start = pos;

        Point cropped_delta {0, 0};

        if(abs(drag_buffer.x) > 16)
        {
            cropped_delta.x = (drag_buffer.x / 16) * 16;
            drag_buffer.x = drag_buffer.x % 16;
        }

        if(abs(drag_buffer.y) > 16)
        {
            cropped_delta.y = (drag_buffer.y / 16) * 16;
            drag_buffer.y = drag_buffer.y % 16;
        }

        auto& tile = *drag_target.tile;
        scale_tile(drag_target, cropped_delta);
        game::apply_tile_constraints(*(level()));
        tile.area_past = tile.area;
    }
}

