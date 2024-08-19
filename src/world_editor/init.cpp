#include "world_editor/world_editor.hpp"
#include "world_editor/data.hpp"


namespace WE
{
    MouseFocus mouse_focus;

    vector<Button> global_buttons, level_buttons;
}


void WE::init(int, char**, scene_uid)
{
    level_buttons.emplace_back(Point{4, 4}, "Edit", &edit_level, "edit");
    level_buttons.emplace_back(Point{-4, 4}, "Clone", &clone_level, "copy");
    level_buttons.emplace_back(Point{-4, -4}, "Delete", &delete_level, "delete");

    global_buttons.emplace_back(Point{-32, -32}, "New", &new_level, "create");

    for(auto& btn : level_buttons)
        generate_button_label(btn);
    for(auto& btn : global_buttons)
        generate_button_label(btn);
}

void WE::deinit(scene_uid)
{

}
