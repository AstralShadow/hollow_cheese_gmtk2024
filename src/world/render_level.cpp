#include "core/core.hpp"
#include "world/level.hpp"
#include "world/render.hpp"
#include "world/data.hpp" // PickedTile drag_target
#include "game/object.hpp"
#include "game/sprite.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;
using std::min;

static auto& rnd = core::renderer;


void world::render_level(Level const& level, float scale, bool debug)
{
    SDL_SetRenderDrawColor(rnd, 0x05, 0x12, 0x1a, 255);
    SDL_RenderFillRect(rnd, nullptr);


    for(auto const& tile : level.tiles) // Z == 0
    {
        FRect area {
            static_cast<float>(tile.area.x),
            static_cast<float>(tile.area.y),
            static_cast<float>(tile.area.w),
            static_cast<float>(tile.area.h)
        };

        if(scale != 1.0f)
        {
            area *= scale;
        }

        SDL_SetRenderDrawColor(rnd, 0x00, 0x15, 0x2b, 255);
        SDL_RenderFillRectF(rnd, &area);

        bool is_anchored = tile.mandatory_area.x > 0 || tile.mandatory_area.y > 0;
        if(is_anchored) {
            SDL_SetRenderDrawColor(rnd, 255, 128, 0, 255); // orange

            FRect m_area {
                static_cast<float>(tile.mandatory_area.x),
                static_cast<float>(tile.mandatory_area.y),
                static_cast<float>(tile.mandatory_area.w),
                static_cast<float>(tile.mandatory_area.h)
            };
            m_area *= scale;
            SDL_RenderFillRectF(rnd, &m_area);
        }

        for(size_t side = 0; side < tile.scalable.size(); side++)
        {
            if(&tile == drag_target.tile && side == drag_target.side)
                SDL_SetRenderDrawColor(rnd, 0xff, 0xff, 0xff, 255);
            else if(tile.scalable[side])
                SDL_SetRenderDrawColor(rnd, 0x58, 0xd2, 0xff, 255);
            else 
                SDL_SetRenderDrawColor(rnd, 0x00, 0x5d, 0x93, 255);

            size_t thickness = (scale > 0.5 ? 1 : scale) * tile_border_thickness;
            if(thickness < 1)
                thickness = 1;

            switch(side)
            {
            case TOP:
                for(size_t i = 0; i < thickness; i++)
                    SDL_RenderDrawLineF(rnd, area.x,          area.y + i,
                                             area.x + area.w, area.y + i);
                break;

            case RIGHT:
                for(size_t i = 0; i < thickness; i++)
                    SDL_RenderDrawLineF(rnd, area.x + area.w - i, area.y,
                                             area.x + area.w - i, area.y + area.h);
                break;

            case BOTTOM:
                for(size_t i = 0; i < thickness; i++)
                    SDL_RenderDrawLineF(rnd, area.x,          area.y + area.h - i,
                                             area.x + area.w, area.y + area.h - i);
                break;

            case LEFT:
                for(size_t i = 0; i < thickness; i++)
                    SDL_RenderDrawLineF(rnd, area.x + i, area.y,
                                             area.x + i, area.y + area.h);
                break;
            }
        }
    }


    /*
    static const vector<string> layer1_textures = {
        "top decoration double deer",
        "top decoration holy cheese",
        "chain"
    };
    */

    for(auto const& texture : level.textures) // Z == 5
    {
        /*
        bool match = false;
        for(auto t : layer1_textures)
            if(t == texture.name)
                match = true;
        if(!match)
            continue;
        */

        string name = texture.name;
        auto size = game::sprite_size(name);
        FRect area {
            (int) texture.pos.x * scale,
            (int) texture.pos.y * scale,
            (int) size.x * scale,
            (int) size.y * scale
        };

        SDL_RenderCopyF(rnd, game::sprite(name), nullptr, &area);

        if(debug)
        {
            SDL_SetRenderDrawColor(rnd, 0x58, 0xd2, 0xff, 255);
            SDL_RenderDrawRectF(rnd, &area);
        }
    }

    for(auto const& obj : level.objects) // Z == 10
        game::render_object(game::object(obj.name), obj.pos, scale, debug);

}


world::PickedTile world::camera_pick_tile(Level& level, Point pos, bool ignore_scalable_constraints)
{
    const int margin = 10; // ignore tiles beyond that distance

    float pick_rate = -10; // how sure are we that this is the tile we want to pick, capped at 1
    PickedTile result { nullptr };

    for(size_t i = 0; i < level.tiles.size(); i++)
    {
        auto const& tile = level.tiles[i];
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
            result.tile = &(level.tiles[i]);
            result.side = static_cast<direction_t>(pick);
        }
    }

    return result;
}
