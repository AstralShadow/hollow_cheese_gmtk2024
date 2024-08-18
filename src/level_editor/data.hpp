#ifndef INCLUDE_LE_DATA_HPP
#define INCLUDE_LE_DATA_HPP

#include "utils/types.hpp"
#include "world/data.hpp"
//#include "world_editor/data.hpp"

namespace LE
{
    extern int target_level;

    world::Level* level();


    void render_levels(); // Rendered at 80% from screen
}

#endif // INCLUDE_LE_DATA_HPP
