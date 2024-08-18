#include "world_editor/world_editor.hpp"
#include "world_editor/data.hpp"


namespace WE
{
    MouseFocus mouse_focus;

    vector<Button> buttons;
}


void WE::init(int, char**, scene_uid)
{
    buttons.emplace_back(Point{-4, 4}, "Clone");
    buttons.emplace_back(Point{-4, -4}, "Edit");
    buttons.emplace_back(Point{4, -4}, "Delete");
}

void WE::deinit(scene_uid)
{

}
