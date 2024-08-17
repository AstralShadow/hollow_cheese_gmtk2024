#include "game/data.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::update_collisions(Map& map, vector<Player>&)
{
    apply_tile_constraints(map);
}

// Typically, this implementation here can be buggy.
// Practically, since only one tile may be scaled between ticks, it should work fine.
void game::apply_tile_constraints(Map& map)
{
    for(auto& tile : map.tiles)
    {
        if(tile.area == tile.area_past)
            continue;

/*
        Point directions[4] { // top, right, bottom, left
            {0, -1},
            {1, 0},
            {0, 1},
            {-1, 0}
        };
*/


        /* Enlarging */

        bool en_init_flag[4] = {0, 0, 0, 0};
        int en_lim[4] = {0, 0, 0, 0};

        for(auto const& other : map.tiles) // on X axis
        {
            // rule out tiles that don't match the Y axis
            if(other.area.y > tile.area.y + tile.area.h)
                continue;
            if(other.area.y + other.area.h < tile.area.y)
                continue;
            if(&other == &tile)
                continue;

            if(tile.area.x < tile.area_past.x) // To the left
            {
                auto left_lim = other.area.x + other.area.w;
                if(left_lim <= tile.area_past.x) // Limit to left of this tile
                if(!en_init_flag[LEFT] || en_lim[LEFT] < left_lim) {
                    en_lim[LEFT] = left_lim;
                    en_init_flag[LEFT] = true;
                }
            }

            if(tile.area.x + tile.area.w > tile.area_past.x + tile.area_past.w) // To the right
            {
                auto right_lim = other.area.x;
                if(right_lim >= tile.area_past.x + tile.area_past.w) // Limit to right of this tile
                if(!en_init_flag[RIGHT] || en_lim[RIGHT] > right_lim) {
                    en_lim[RIGHT] = right_lim;
                    en_init_flag[RIGHT] = true;
                }
            }
        }

        for(auto const& other : map.tiles) // on Y axis
        {
            // rule out tiles that don't match the X axis
            if(other.area.x > tile.area.x + tile.area.w)
                continue;
            if(other.area.x + other.area.w < tile.area.x)
                continue;
            if(&other == &tile)
                continue;

            if(tile.area.y < tile.area_past.y) // To the top
            {
                auto top_lim = other.area.y + other.area.h;
                if(top_lim <= tile.area_past.y) // Limit to over this tile
                if(!en_init_flag[TOP] || en_lim[TOP] < top_lim) {
                    en_lim[TOP] = top_lim;
                    en_init_flag[TOP] = true;
                }
            }

            if(tile.area.y + tile.area.h > tile.area_past.y + tile.area_past.h) // To the bottom
            {
                auto bottom_lim = other.area.y;
                if(bottom_lim >= tile.area_past.y + tile.area_past.h) // Limit to below this tile
                if(!en_init_flag[BOTTOM] || en_lim[BOTTOM] > bottom_lim) {
                    en_lim[BOTTOM] = bottom_lim;
                    en_init_flag[BOTTOM] = true;
                }
            }
        }

        /* Sanity checks */ {
            bool error = false;
            if(en_init_flag[TOP] && en_lim[TOP] > tile.area_past.y)
            {
                cout << "Limit error: TOP" << endl;
                error = true;
            }
            if(en_init_flag[RIGHT] && en_lim[RIGHT] < tile.area_past.x + tile.area_past.w)
            {
                cout << "Limit error: RIGHT" << endl;
                error = true;
            }

            if(en_init_flag[BOTTOM] && en_lim[BOTTOM] < tile.area_past.y + tile.area_past.h)
            {
                cout << "Limit error: BOTTOM" << endl;
                error = true;
            }

            if(en_init_flag[LEFT] && en_lim[LEFT] > tile.area_past.x)
            {
                cout << "Limit error: LEFT" << endl;
                error = true;
            }

            if(error) {
                cout << "[tile lim debug data start]" << endl;
                cout << "x: " << tile.area_past.x << " -> " << tile.area.x << endl;
                cout << "y: " << tile.area_past.y << " -> " << tile.area.y << endl;
                cout << "w: " << tile.area_past.w << " -> " << tile.area.w << endl;
                cout << "h: " << tile.area_past.h << " -> " << tile.area.h << endl;
                cout << endl;
                cout << "lim x:" << en_lim[LEFT] << endl;
                cout << "lim y:" << en_lim[TOP] << endl;
                cout << "lim w:" << en_lim[RIGHT] << endl;
                cout << "lim h:" << en_lim[BOTTOM] << endl;
                cout << endl;
                cout << "[tile lim debug data end]" << endl;
            }
        }

        /* Apply enlarging limits */
        if(en_init_flag[TOP] && en_lim[TOP] > tile.area.y)
        {
            tile.area.h -= en_lim[TOP] - tile.area.y;
            tile.area.y = en_lim[TOP];
        }

        if(en_init_flag[RIGHT] && en_lim[RIGHT] < tile.area.x + tile.area.w)
        {
            tile.area.w = en_lim[RIGHT] - tile.area.x;
        }

        if(en_init_flag[BOTTOM] && en_lim[BOTTOM] < tile.area.y + tile.area.h)
        {
            tile.area.h = en_lim[BOTTOM] - tile.area.y;
        }

        if(en_init_flag[LEFT] && en_lim[LEFT] > tile.area.x)
        {
            tile.area.w -= en_lim[LEFT] - tile.area.x;
            tile.area.x = en_lim[LEFT];
        }


        /* Shrinking */


        tile.area_past = tile.area;
    }
}
