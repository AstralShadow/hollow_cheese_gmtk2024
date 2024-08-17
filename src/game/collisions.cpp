#include "game/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::update_collisions(Map& map, vector<Player>&)
{
    apply_tile_constraints(map);
}

