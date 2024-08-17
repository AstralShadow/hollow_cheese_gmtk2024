#include "game/data.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::max;
using std::min;


void game::update_collisions(Map& map, vector<Player>& players)
{
    apply_tile_constraints(map);

    // When it comes to players, I think I'd prefer horizontal collisions applied first.

    //apply_player_player_collisions(Player&);

    for(auto& player : players)
        apply_player_tile_collisions(map, player);


    for(auto& tile : map.tiles)
        tile.area_past = tile.area;

    for(auto& player : players)
        player.area_past = player.area;
}

void game::apply_player_tile_collisions(Map& map, Player& player)
{
    /* Horizontal tile collision */

    struct TPC_data // Tile-Player Collision data
    {
        int dist;
        Tile* tile = nullptr;
    };
    vector<TPC_data> left; // TODO don't use vectors. Use single values instead
    vector<TPC_data> right;

    // TODO If a player is being squashed, see if nearby tile got scaled and shrink a bit
    for(auto& tile : map.tiles)
    {
        // rule out tiles that don't match the Y axis
        if(tile.area.y > player.area.y + player.area.h - player.step_height)
            continue;
        if(tile.area.y + tile.area.h < player.area.y)
            continue;

        if(tile.area.x + tile.area.w / 2 < player.area.x + player.area.w / 2)
        {
            int dist = player.area.x - (tile.area.x + tile.area.w);
            auto itr = left.begin();
            while(itr != left.end() && itr->dist < dist)
                itr++;
            left.insert(itr, {dist, &tile});
        }
        else
        {
            int dist = tile.area.x - (player.area.x + player.area.w);
            auto itr = right.begin();
            while(itr != right.end() && itr->dist < dist)
                itr++;
            right.insert(itr, {dist, &tile});
        }
    }

    if(left.size() && right.size() && left[0].dist + right[0].dist < 0) // being squashed
    {
        auto& tile1 = *(left[0].tile);
        auto& tile2 = *(right[0].tile);

        const int _debt = -(left[0].dist + right[0].dist);
        int debt = _debt;

        int dist_l = -1, dist_r = -1; // Moved out for logging purposes

        // Prioritize left if currently moved.
        // Otherwise use right.
        // Otherwise use left if not moved.

        if(tile1.area == tile1.area_past)
        {
            int cap = tile1.area.x + tile1.min_size.x;

            bool is_anchored = tile1.mandatory_area.x > 0 || tile1.mandatory_area.y > 0;
            if(is_anchored)
                cap = max(cap, tile1.mandatory_area.x + tile1.mandatory_area.w);

            // int dist_l;
            dist_l = min(debt, tile1.area.w + tile1.area.x - cap);
            tile1.area.w -= dist_l;
            debt -= dist_l;
        }

        if(debt > 0)
        {
            int cap = tile2.area.x + tile2.area.w - tile2.min_size.x;

            bool is_anchored = tile2.mandatory_area.x > 0 || tile2.mandatory_area.y > 0;
            if(is_anchored)
                cap = min(cap, tile2.mandatory_area.x);

            // int dist_r;
            dist_r = min(debt, cap - tile2.area.x);
            tile2.area.x += dist_r;
            tile2.area.w -= dist_r;
            debt -= dist_r;
        }

        if(debt > 0 && tile1.area != tile1.area_past)
        {
            int cap = tile1.area.x + tile1.min_size.x;

            bool is_anchored = tile1.mandatory_area.x > 0 || tile1.mandatory_area.y > 0;
            if(is_anchored)
                cap = max(cap, tile1.mandatory_area.x + tile1.mandatory_area.w);

            // int dist_l;
            dist_l = min(debt, tile1.area.w + tile1.area.x - cap);
            tile1.area.w -= dist_l;
            debt -= dist_l;
        }

        player.area.x = tile1.area.x + tile1.area.w;

        if(debt > 0)
        {
            cout << "Player got squished and couldn't figure what tile to shrink." << endl;
            cout << "Initial squish debt: " << _debt << endl;
            cout << "Left cushion used: " << dist_l << endl;
            cout << "Right cushion used: " << dist_r << endl;
            cout << "Leftover debt: " << debt << endl;
        }
    }
    else if(left.size() && left[0].dist < 0)
        player.area.x += -left[0].dist;
    else if(right.size() && right[0].dist < 0)
        player.area.x -= -right[0].dist;

    cout << "left: ";
    for(auto a : left) {
        cout << a.dist << " ";
    }
    cout << endl;
    cout << "right: ";
    for(auto a : right) {
        cout << a.dist << " ";
    }
    cout << endl;

    // TODO resume this


    /* Vertical collisions */
    vector<TPC_data> ground;

    // Should i be figuring out the ground from the previous tick?

    for(auto const& tile : map.tiles)
    {
        const int extra_horizontal_reach = 16;
        const bool moving_right = player.velocity.x > 0.0f;
        const bool moving_left = player.velocity.x < 0.0f;

        // rule out tiles that don't match the X axis
        if(tile.area.x > player.area.x + player.area.w + extra_horizontal_reach * moving_right)
            continue;
        if(tile.area.x + tile.area.w < player.area.x - extra_horizontal_reach * moving_left)
            continue;

        // rule out stuff too high
        if(tile.area.y > player.area.y + player.area.h - player.step_height)
            continue;

        // TODO resume this
    }
}

