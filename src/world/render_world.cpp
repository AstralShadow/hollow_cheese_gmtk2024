#include "core/core.hpp"
#include "world/level.hpp"
#include "world/render.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;
using std::min;

static auto& rnd = core::renderer;

static const Point level_size { WINDOW_WIDTH, WINDOW_HEIGHT };


void world::render_world(World const& world, bool ignore_exploration_flag)
{
    FPoint pixel_scale {
        1.0f * level_size.x / world.size.x,
        1.0f * level_size.y / world.size.y
    };

    for(size_t i = 0; i < world.levels.size(); ++i)
    {
        auto const& data = world.levels[i];
        SDL_Rect area {
            static_cast<int>(data.pos.x * pixel_scale.x),
            static_cast<int>(data.pos.y * pixel_scale.y),
            static_cast<int>((data.pos.x + level_size.x) * pixel_scale.x),
            static_cast<int>((data.pos.y + level_size.y) * pixel_scale.y)
        };
        area.w -= area.x; // Doing this should negate some of the float rounding error
        area.h -= area.y;

        SDL_RenderSetViewport(rnd, &area);

        if(ignore_exploration_flag || data.explored)
        {
            if(pixel_scale.x == pixel_scale.y)
                render_level(data.level, pixel_scale.x);
            else
            {
                SDL_RenderSetScale(rnd, pixel_scale.x, pixel_scale.y);
                render_level(data.level);
                SDL_RenderSetScale(rnd, 1, 1);
            }
        }
        else
        {
            SDL_SetRenderDrawColor(rnd, 32, 32, 32, 255);
            SDL_RenderFillRect(rnd, nullptr);
        }

        if(data.reachable)
            SDL_SetRenderDrawColor(rnd, 128, 128, 128, 255);
        else
            SDL_SetRenderDrawColor(rnd, 196, 0, 0, 255);
        SDL_RenderDrawRect(rnd, nullptr);

        if(i == world.current_level)
        {
            SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
            SDL_RenderDrawRect(rnd, nullptr);
        }
    }

    SDL_RenderSetViewport(rnd, nullptr);
    SDL_RenderSetScale(rnd, 1, 1);
}


world::PickedLevel world::camera_pick_level(World const& world, Point pos)
{
    FPoint pixel_scale {
        1.0f * level_size.x / world.size.x,
        1.0f * level_size.y / world.size.y
    };

    for(size_t i = 0; i < world.levels.size(); ++i)
    {
        auto const& data = world.levels[i];
        SDL_Rect area {
            static_cast<int>(data.pos.x * pixel_scale.x),
            static_cast<int>(data.pos.y * pixel_scale.y),
            static_cast<int>((data.pos.x + level_size.x) * pixel_scale.x),
            static_cast<int>((data.pos.y + level_size.y) * pixel_scale.y)
        };
        area.w -= area.x; // Doing this should negate some of the float rounding error
        area.h -= area.y;

        if(SDL_PointInRect(&pos, &area))
        {
            return PickedLevel{
                .level = static_cast<int>(i),
                .area = area,
                .pos = {pos.x - area.x, pos.y - area.y}
            };
        }
    }

    return {};
}

