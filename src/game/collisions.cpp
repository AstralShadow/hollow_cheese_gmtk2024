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


        /* Tile collisions (enlarging) */

        bool en_init_flag[4] = {0, 0, 0, 0};
        int en_lim[4] = {0, 0, 0, 0};

        const bool ext_left = tile.area.x < tile.area_past.x;
        const bool ext_right = tile.area.x + tile.area.w > tile.area_past.x + tile.area_past.w;
        const bool ext_upwards = tile.area.y < tile.area_past.y;
        const bool ext_downwards = tile.area.y + tile.area.h > tile.area_past.y + tile.area_past.h;

        if(ext_left || ext_right)
        for(auto const& other : map.tiles) // on X axis
        {
            // rule out tiles that don't match the Y axis
            if(other.area.y > tile.area.y + tile.area.h)
                continue;
            if(other.area.y + other.area.h < tile.area.y)
                continue;

            if(&other == &tile)
                continue;

            if(ext_left)
            {
                auto left_lim = other.area.x + other.area.w;
                if(left_lim <= tile.area_past.x) // Limit to left of this tile
                if(!en_init_flag[LEFT] || en_lim[LEFT] < left_lim) {
                    en_lim[LEFT] = left_lim;
                    en_init_flag[LEFT] = true;
                }
            }

            if(ext_right)
            {
                auto right_lim = other.area.x;
                if(right_lim >= tile.area_past.x + tile.area_past.w) // Limit to right of this tile
                if(!en_init_flag[RIGHT] || en_lim[RIGHT] > right_lim) {
                    en_lim[RIGHT] = right_lim;
                    en_init_flag[RIGHT] = true;
                }
            }
        }

        if(ext_upwards || ext_downwards)
        for(auto const& other : map.tiles) // on Y axis
        {
            // rule out tiles that don't match the X axis
            if(other.area.x > tile.area.x + tile.area.w)
                continue;
            if(other.area.x + other.area.w < tile.area.x)
                continue;

            if(&other == &tile)
                continue;

            if(ext_upwards)
            {
                auto top_lim = other.area.y + other.area.h;
                if(top_lim <= tile.area_past.y) // Limit to over this tile
                if(!en_init_flag[TOP] || en_lim[TOP] < top_lim) {
                    en_lim[TOP] = top_lim;
                    en_init_flag[TOP] = true;
                }
            }

            if(ext_downwards)
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


        /* Mandatory area (shrinking) */

        bool is_anchored = tile.mandatory_area.x > 0 || tile.mandatory_area.y > 0;
        if(is_anchored)
        {
            auto& area = tile.area;
            auto const& area_past = tile.area_past;
            auto const& mandatory_area = tile.mandatory_area;

            const bool sh_left = area.x > area_past.x;
            const bool sh_right = area.x + area.w < area_past.x + area_past.w;
            const bool sh_upwards = area.y > area_past.y;
            const bool sh_downwards = area.y + area.h < area_past.y + area_past.h;

            if(sh_left && area.x > mandatory_area.x)
            {
                area.w += area.x - mandatory_area.x;
                area.x = mandatory_area.x;
            }

            if(sh_right && area.x + area.w < mandatory_area.x + mandatory_area.w)
            {
                area.w = mandatory_area.x + mandatory_area.w - area.x;
            }

            if(sh_upwards && area.y > mandatory_area.y)
            {
                area.h += area.y - mandatory_area.y;
                area.y = mandatory_area.y;
            }

            if(sh_downwards && area.y + area.h < mandatory_area.y + mandatory_area.h)
            {
                area.h = mandatory_area.y + mandatory_area.h - area.y;
            }
        }


        tile.area_past = tile.area;
    }
}
