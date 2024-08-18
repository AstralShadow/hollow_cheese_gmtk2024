#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"


namespace LE
{
    int target_level = 0;
    mode_t mode = EDIT_MODE;

    vector<Player> players;
    int active_players = 2;

    bool simulate_game = true;

    //vector<Button> buttons;
}

world::Level* LE::level()
{
    if(target_level > -1 && (size_t) target_level < world::world.levels.size())
        return &(world::world.levels[target_level].level);
    return nullptr;
}



void LE::init(int, char**, scene_uid)
{
    players.push_back(Player
    {
        .area = {0, 200, 32, 64}
    });
    players.push_back(Player
    {
        .area = {128, 200, 32, 64},
        .controls = {
            SDL_SCANCODE_UP,
            SDL_SCANCODE_RIGHT,
            SDL_SCANCODE_DOWN,
            SDL_SCANCODE_LEFT
        }
    });

    //buttons.emplace_back(Point{-4, 4}, "", &clone_level);

    //for(auto& btn : buttons)
    //    generate_button_label(btn);
}

void LE::deinit(scene_uid)
{

}
