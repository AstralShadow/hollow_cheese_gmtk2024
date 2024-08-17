#include "game/game.hpp"
#include "core/core.hpp"
#include "game/render.hpp"
#include "game/data.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;
using std::min;

static auto& rnd = core::renderer;


void game::render_level(Map const& map)
{
    for(auto const& tile : map.tiles)
    {
        auto& area = tile.area;
        SDL_SetRenderDrawColor(rnd, 0, 0, 0, 196); // black
        SDL_RenderFillRect(rnd, &area);
        SDL_SetRenderDrawColor(rnd, 0, 128, 0, 255); // dark green
        SDL_RenderDrawRect(rnd, &area);

        for(size_t side = 0; side < tile.scalable.size(); side++)
        {
            if(!tile.scalable[side])
                continue;

            if(&tile == drag_target.tile && side == drag_target.side)
                SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255); // yellow
            else
                SDL_SetRenderDrawColor(rnd, 0, 255, 255, 255); // cyan/lime


            switch(side)
            {
            case TOP:
                SDL_RenderDrawLine(rnd, area.x, area.y,
                                        area.x + area.w, area.y);
                break;

            case RIGHT:
                SDL_RenderDrawLine(rnd, area.x + area.w, area.y,
                                        area.x + area.w, area.y + area.h);
                break;

            case BOTTOM:
                SDL_RenderDrawLine(rnd, area.x, area.y + area.h,
                                        area.x + area.w, area.y + area.h);
                break;

            case LEFT:
                SDL_RenderDrawLine(rnd, area.x, area.y,
                                        area.x, area.y + area.h);
                break;
            }
        }
    }
}

game::PickedTile game::camera_pick_tile(Map& map, Point pos, bool ignore_scalable_constraints)
{
    const int margin = 10; // ignore tiles beyond that distance

    float pick_rate = -10; // how sure are we that this is the tile we want to pick, capped at 1
    PickedTile result { nullptr };

    for(size_t i = 0; i < map.tiles.size(); i++)
    {
        auto const& tile = map.tiles[i];
        auto const& area = tile.area;

        if(area.x > pos.x + margin)
            continue;
        if(area.y > pos.y + margin)
            continue;
        if(area.x + area.w <= pos.x - margin)
            continue;
        if(area.y + area.h <= pos.y - margin)
            continue;


        // Positive distance towards the center
        int dist[4] = { // top, right, bottom, left
            min(pos.y - area.y, area.h),
            min(area.x + area.w - pos.x, area.w),
            min(area.y + area.h - pos.y, area.h),
            min(pos.x - area.x, area.w)
        };

        int min_dist, pick = -1;
        for(int j = 0; j < 4; j++) {
            if(tile.scalable[j] || ignore_scalable_constraints) {
                min_dist = dist[j];
                pick = j;
                break;
            }
        }

        if(pick == -1) // Tile not scalable
            continue;

        for(int j = pick + 1; j < 4; j++)
        {
            if(tile.scalable[j] || ignore_scalable_constraints)
            if(min_dist > dist[j]) {
                min_dist = dist[j];
                pick = j;
            }
        }


        float rate = 0;
        for(int j = 0; j < 4; j++)
            rate += dist[j];
        rate /= area.w + area.h; // Normalize; cap to 1

        if(!result.tile || rate > pick_rate)
        {
            pick_rate = rate;
            result.tile = &(map.tiles[i]);
            result.side = static_cast<direction_t>(pick);
        }
    }

    return result;
}
