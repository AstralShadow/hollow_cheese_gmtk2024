#include "menu/menu.hpp"
#include "game/fonts.hpp"
#include "core/core.hpp"
#include "utils/screen.hpp"
#include "utils/textures.hpp"
#include <SDL2/SDL_render.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

static auto& rnd = core::renderer;


void menu::render(scene_uid)
{
    static auto texture = utils::load_texture("assets/menu/red/view-menu.png");
    SDL_RenderCopy(rnd, texture, nullptr, nullptr);
    SDL_RenderPresent(rnd);
}
