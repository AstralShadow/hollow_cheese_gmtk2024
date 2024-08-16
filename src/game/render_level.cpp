#include "game/game.hpp"
#include "core/core.hpp"
#include "game/render.hpp"
#include "game/data.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void game::render_level(Map const& map)
{
    for(auto tile : map.tiles)
    {
        auto& area = tile.area;
        SDL_SetRenderDrawColor(rnd, 0, 0, 0, 196);
        SDL_RenderFillRect(rnd, &area);
        SDL_SetRenderDrawColor(rnd, 0, 128, 0, 255);
        SDL_RenderDrawRect(rnd, &area);
        SDL_SetRenderDrawColor(rnd, 0, 255, 255, 255);

        for(size_t i = 0; i < tile.scalable.size(); i++)
        {
            if(!tile.scalable[i])
                continue;

            switch(i)
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
