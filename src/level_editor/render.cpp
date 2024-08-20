#include "level_editor/level_editor.hpp"
#include "core/core.hpp"
#include "world/render.hpp"
#include "level_editor/data.hpp"
#include "game/render.hpp"
#include "game/fonts.hpp"
#include "utils/textures.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_mouse.h>
#include <iostream>

using std::cout;
using std::endl;
using std::max;
using std::min;

static auto& rnd = core::renderer;


void LE::render(scene_uid)
{
    if(!level())
    {
        core::set_scene("world_editor");
        return;
    }


    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_levels();

    switch(mode)
    {
    case EDIT_MODE:
        break;
    case OBJECT_MODE:
        render_object_mode_menu();
        break;
    case TEXTURE_MODE:
        render_texture_mode_menu();
        break;
    }

    render_buttons();
    render_error_message();

    SDL_RenderPresent(rnd);
}


void LE::render_levels()
{
    SDL_Rect area {
        32,
        48,
        static_cast<int>(WINDOW_WIDTH * 0.8),
        static_cast<int>(WINDOW_HEIGHT * 0.8)
    };

    SDL_RenderSetViewport(rnd, &area);

    bool debug = true;
    world::render_level(*(level()), 0.8, debug);
    render_grid(*(level()), 0.8);


    SDL_RenderSetScale(rnd, 0.8, 0.8);
    game::render_players(players.begin(), players.begin() + active_players);
    SDL_RenderSetScale(rnd, 1, 1);
    render_player_overlays(0.8);


    SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    SDL_RenderDrawRect(rnd, nullptr);


    const Point level_size = { WINDOW_WIDTH, WINDOW_HEIGHT };
    Point level_pos = world::world.levels[target_level].pos;
    Rect screen {
        level_pos.x - level_size.x / 8,
        level_pos.y - level_size.y / 8,
        static_cast<int>(level_size.x * 1.25),
        static_cast<int>(level_size.y * 1.25)
    };

    for(auto const& data : world::world.levels)
    {
        auto const& pos = data.pos;
        if(pos.x <= screen.x + screen.w)
        if(pos.y <= screen.y + screen.h)
        if(pos.x + level_size.x > screen.x)
        if(pos.y + level_size.y > screen.y)
        if(&data.level != level())
        {
            SDL_Rect area2 {
                static_cast<int>((pos.x - level_pos.x) * 0.8) + area.x,
                static_cast<int>((pos.y - level_pos.y) * 0.8) + area.y,
                area.w,
                area.h
            };
            SDL_RenderSetViewport(rnd, &area2);

            world::render_level(data.level, 0.8);

            SDL_SetRenderDrawColor(rnd, 0, 0, 0, 96);
            SDL_RenderFillRect(rnd, nullptr);
        }
    }

    SDL_RenderSetViewport(rnd, nullptr);
}

Point LE::get_level_coordinates(Point screen_pos)
{
    SDL_Point offset { // Should be synced with the above
        32,
        48
    };
    float scale = 0.8;

    return {
        static_cast<int>((screen_pos.x - offset.x) / scale),
        static_cast<int>((screen_pos.y - offset.y) / scale)
    };
}


void LE::render_player_overlays(float scale)
{
    if(!jump_prediction)
        return;

    // Only render path prediction near mouse
    SDL_Point _mouse;
    SDL_GetMouseState(&_mouse.x, &_mouse.y);
    SDL_Point mouse = get_level_coordinates(_mouse);
    const int range = 128;
    const int range2 = range * range;

    SDL_RenderSetScale(rnd, scale, scale);
    for(int i = 0; i < active_players; i++)
    {
        auto itr = players.begin() + i; // Needs an iterator to match an interface
        auto const& player = *itr;

        float dx = player.area.x + player.area.w / 2 - mouse.x;
        float dy = player.area.y + player.area.h / 2 - mouse.y;
        if(dx*dx + dy*dy > range2 && jump_prediction != 1)
            continue;

        game::render_players_jump_reach(*level(), itr, itr + 1);
    }
    SDL_RenderSetScale(rnd, 1, 1);
}

void LE::render_grid(Level const&, float scale)
{
    /* Default grid (16x16), only near mouse */
    {
        SDL_Point _mouse;
        SDL_GetMouseState(&_mouse.x, &_mouse.y);
        SDL_Point mouse = get_level_coordinates(_mouse);
        const int range = 56;

        SDL_SetRenderDrawColor(rnd, 196, 196, 196, 128);

        int x = max(0, mouse.x - range);
        x += (x % 16) ? (16 - x % 16) : 0;
        for(; x < min(WINDOW_WIDTH, mouse.x + range); x = (x + 16) - (x % 16))
        {
            float y1 = mouse.y + sqrt(range * range - (x - mouse.x) * (x - mouse.x));
            float y2 = 2 * mouse.y - y1;
            SDL_RenderDrawLineF(rnd, x * scale, y1 * scale, x * scale, y2 * scale);
        }

        int y = max(0, mouse.y - range);
        y += (y % 16) ? (16 - y % 16) : 0;
        for(; y < min(WINDOW_HEIGHT, mouse.y + range); y = (y + 16) - (y % 16))
        {
            float x1 = mouse.x + sqrt(range * range - (y - mouse.y) * (y - mouse.y));
            float x2 = 2 * mouse.x - x1;
            SDL_RenderDrawLineF(rnd, x1 * scale, y * scale, x2 * scale, y * scale);
        }
    }

    // TODO render hint guide lines, if any
}

void LE::render_buttons()
{
    for(auto& btn : buttons)
    {
        if(active_players && btn.icon == "player_count")
            btn.focused = true;

        if(time_pause && btn.icon == "time_pause")
            btn.focused = true;
        if(slow_motion && btn.icon == "slow_motion")
            btn.focused = true;
        if(jump_prediction && btn.icon == "jump_prediction")
            btn.focused = true;

        render_button(btn, btn.pos);
    }


    string mode = "none";
    switch(LE::mode)
    {
        case EDIT_MODE:
            mode = "edit_mode";
            break;
        case OBJECT_MODE:
            mode = "object_mode";
            break;
        case TEXTURE_MODE:
            mode = "texture_mode";
            break;
    }

    for(auto& btn : mode_buttons)
    {
        if(mode == btn.icon)
            btn.focused = true;

        render_button(btn, btn.pos);
    }
}

void LE::render_error_message()
{
    static string message = "";
    static SDL_Texture* notice = nullptr;
    static Rect area;

    if(message != last_action_error)
    {
        if(notice)
            SDL_DestroyTexture(notice);

        message = last_action_error;

        auto font = game::get_font();
        SDL_Color color {196, 0, 0, 255};

        auto surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);
        if(!surf) {
            cout << "Failed to render error message" << endl;
            cout << TTF_GetError() << endl;
            return;
        }

        notice = utils::create_texture(surf);
        area = Rect {
            32 + 8 * 3,
            WINDOW_HEIGHT - surf->h - 16,
            surf->w,
            surf->h
        };

        SDL_FreeSurface(surf);
    }

    if(notice && !message.empty())
        SDL_RenderCopy(rnd, notice, nullptr, &area);
}
