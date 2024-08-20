#include "world_editor/data.hpp"
#include "level_editor/data.hpp"
#include "core/scene.hpp"
#include <iostream>

using std::cout;
using std::endl;

// TODO add export features


void WE::new_level()
{
    Point pos = world::find_empty_level_pos(mouse_focus.level);
    if(pos.x == -1 && pos.y == -1) {
        cout << "Could not find a position to create new level at." << endl;
        return;
    }

    world::Level new_level;
    world::world.levels.push_back(
        world::LevelData {
            .level = new_level,
            .pos = pos,
            .explored = false
        }
    );
}

void WE::edit_level()
{
    LE::target_level = mouse_focus.level;
    core::set_scene("level_editor");

    // Cleanup
    mouse_focus.dragging = false;
    mouse_focus.selected = false;
    mouse_focus.level = -1;

    world::save_world();
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

