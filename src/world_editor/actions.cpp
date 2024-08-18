#include "world_editor/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


void WE::edit_level()
{
    cout << "edit: " << mouse_focus.level << endl;
    cout << "edit not implemented" << endl;
}

void WE::clone_level()
{
    Point pos = world::find_empty_level_pos(mouse_focus.level);
    if(pos.x == -1 && pos.y == -1) {
        cout << "Could not find a position to clone the level to." << endl;
        return;
    }

    if((int) world::world.current_level > mouse_focus.level)
        world::world.current_level++;

    world::Level copy = world::world.levels[mouse_focus.level].level;
    world::world.levels.insert(
        world::world.levels.begin() + mouse_focus.level + 1,
        world::LevelData {
            .level = copy,
            .pos = pos,
            .explored = false
        }
    );
}

void WE::delete_level()
{
    if((int) world::world.current_level > mouse_focus.level)
        world::world.current_level--;

    world::world.levels.erase(world::world.levels.begin() + mouse_focus.level);

    mouse_focus.level = -1;
    mouse_focus.selected = false;
}
