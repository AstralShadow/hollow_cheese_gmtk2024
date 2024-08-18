#include "level_editor/level_editor.hpp"
#include "level_editor/data.hpp"
#include "core/scene.hpp"
#include <iostream>

using std::cout;
using std::endl;


void LE::tick(u32, scene_uid)
{
    if(!level()) // fall back to WE
        core::set_scene("world_editor");
}
