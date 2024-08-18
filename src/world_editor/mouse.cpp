#include "world_editor/world_editor.hpp"
#include "core/core.hpp"
#include "world_editor/data.hpp"
#include "world/render.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;

static const Point level_size { WINDOW_WIDTH, WINDOW_HEIGHT };

static FPoint motion_buffer {0, 0};
static int motion_distance = 0;
static const int maximum_click_motion_dist = 10;

void WE::mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    if(mouse_focus.level == -1)
        return;

    if(mouse_focus.selected && button_on_pos({ev.x, ev.y}))
        return;

    mouse_focus.dragging = true;
    motion_distance = 0;

    // Let go of selected level if clicking outside its area
    {
        auto pick = camera_pick_level(world::world, {ev.x, ev.y});

        if(pick.level != mouse_focus.level)
            mouse_focus.selected = false;

        mouse_focus.level = pick.level;
        mouse_focus.area = pick.area;
        mouse_focus.pos = pick.pos;
    }
}

void WE::mouseup(SDL_MouseButtonEvent& ev, scene_uid)
{
    mouse_focus.dragging = false;
    motion_buffer = {0, 0};

    if(click_button({ev.x, ev.y}))
        return;

    if(motion_distance < maximum_click_motion_dist)
        mouse_focus.selected = !mouse_focus.selected;

    if(mouse_focus.level == -1)
        mouse_focus.selected = false;
}

void WE::mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    if(mouse_focus.level != -1 && mouse_focus.dragging)
    {
        motion_distance += abs(ev.xrel) + abs(ev.yrel);

        auto& world = world::world;

        FPoint scale {
            world.size.x * 1.0f / level_size.x,
            world.size.y * 1.0f / level_size.y
        };

        motion_buffer.x += ev.xrel * scale.x;
        motion_buffer.y += ev.yrel * scale.y;

        Point increment {
            static_cast<int>(motion_buffer.x),
            static_cast<int>(motion_buffer.y)
        };

        if(motion_distance > maximum_click_motion_dist)
        {
            move_level(world, mouse_focus.level, increment);

            motion_buffer.x -= increment.x;
            motion_buffer.y -= increment.y;

            // Refresh menu position
            auto pick = camera_pick_level(world::world, {ev.x, ev.y});
            mouse_focus.area = pick.area;
            mouse_focus.pos = pick.pos;
        }
    }
    else if(!mouse_focus.selected || mouse_focus.level == -1)
    {
        auto pick = camera_pick_level(world::world, {ev.x, ev.y});

        mouse_focus.level = pick.level;
        mouse_focus.area = pick.area;
        mouse_focus.pos = pick.pos;
    }


    /* Paint buttons */

    for(auto& btn : level_buttons)
        btn.focused = false;
    for(auto& btn : global_buttons)
        btn.focused = false;

    auto btn = button_on_pos({ev.x, ev.y});
    if(btn)
        btn->focused = true;
}

