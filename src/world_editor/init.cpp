#include "world_editor/world_editor.hpp"
#include "world_editor/data.hpp"


namespace WE
{
    MouseFocus mouse_focus;

    vector<Button> buttons;
}


void WE::init(int, char**, scene_uid)
{
    buttons.emplace_back(Point{-4, 4}, "[C]lone", &clone_level);
    buttons.emplace_back(Point{-4, -4}, "[E]dit", &edit_level);
    buttons.emplace_back(Point{4, -4}, "[D]elete", &delete_level);
}

void WE::deinit(scene_uid)
{

}
