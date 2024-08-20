#include "game/game.hpp"
#include "game/data.hpp"
#include "game/sprite.hpp"
#include <iostream>

using std::cout;
using std::endl;


namespace game
{
    vector<Player> players {
        Player{
            .area = {0, 200, 32, 64}
        },
        {
            .area = {128, 200, 32, 64},
            .controls = {
                SDL_SCANCODE_UP,
                SDL_SCANCODE_RIGHT,
                SDL_SCANCODE_DOWN,
                SDL_SCANCODE_LEFT
            }
        }
    };

    bool enable_level_editor = false;
    Button level_editor_btn = {
        Point {8, WINDOW_HEIGHT - 40},
        "Open in Level Editor",
        &open_level_editor,
        "edit"
    };
}


void game::init(int, char**, scene_uid)
{
    init_sprites();
    generate_button_label(level_editor_btn);
}

void game::deinit(scene_uid)
{

}
