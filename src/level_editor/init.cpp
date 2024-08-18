#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"


namespace LE
{
    int target_level = 0;

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
    //buttons.emplace_back(Point{-4, 4}, "", &clone_level);

    //for(auto& btn : buttons)
    //    generate_button_label(btn);
}

void LE::deinit(scene_uid)
{

}
