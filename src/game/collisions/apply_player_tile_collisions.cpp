#include "game/data.hpp"
#include <iostream>
#include <SDL2/SDL_timer.h>

using std::cout;
using std::endl;
using std::max;
using std::min;

void game::apply_player_tile_collisions(u32 /*ms*/, Map& map, Player& player)
{
    // TODO Refactor. This function is too long and has repeating sections

    /* Horizontal tile collision */

    struct TPC_data // Tile-Player Collision data
    {
        int dist;
        Tile* tile = nullptr;
    };
    vector<TPC_data> left, right; // TODO don't use vectors. Use single values instead

    for(auto& tile : map.tiles)
    {
        // rule out tiles that don't match the Y axis
        if(tile.area.y > player.area.y + player.area.h - player.step_height)
            continue;
        if(tile.area.y + tile.area.h < player.area.y + player.head_height)
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

        // Prioritize unchanged tiles

        if(tile1.scalable[RIGHT] && tile1.area == tile1.area_past)
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

        if(tile2.scalable[LEFT] && debt > 0)
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

        if(dist_l == -1 && tile1.scalable[RIGHT] && debt > 0 && tile1.area != tile1.area_past)
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
            cout << "Above info is not very useful. Attach video and description, please." << endl;
        }
    }
    else if(left.size() && left[0].dist < 0)
        player.area.x += -left[0].dist;
    else if(right.size() && right[0].dist < 0)
        player.area.x -= -right[0].dist;


    /* Vertical collisions */

    vector<TPC_data> floor, roof; // TODO don't use vectors, use single variables instead

    // First check for squishing. Prioritize the direction that the player drags.
    // Then detect the ground from last tick, if any, and adjust height by it.
    // Last, if no ground, cast vertical ground detection and snap up if crashing trough ground.

    // Should i be figuring out the ground from the previous tick?
    for(auto& tile : map.tiles)
    {
        // rule out tiles that don't match the X axis
        if(tile.area.x > player.area.x + player.area.w)
            continue;
        if(tile.area.x + tile.area.w < player.area.x)
            continue;

        if(tile.area.y > player.area.y + player.area.h - player.step_height)
        {
            int dist = tile.area.y - (player.area.y + player.area.h);
            auto itr = floor.begin();
            while(itr != floor.end() && itr->dist < dist)
                itr++;
            floor.insert(itr, {dist, &tile});
        }
        else if(tile.area.y + tile.area.h < player.area.y + player.head_height)
        {
            int dist = player.area.y - (tile.area.y + tile.area.h);
            auto itr = roof.begin();
            while(itr != roof.end() && itr->dist < dist)
                itr++;
            roof.insert(itr, {dist, &tile});
        }
    }

    if(!floor.size() || floor[0].dist > 0)
        player.has_foothold = false;


    if(floor.size() && roof.size() && floor[0].dist + roof[0].dist < 0) // being squashed
    {
        auto& tile1 = *(roof[0].tile);
        auto& tile2 = *(floor[0].tile);

        const int _debt = -(roof[0].dist + floor[0].dist);
        int debt = _debt;

        int dist_t = -1, dist_b = -1; // Moved out for logging purposes

        // Prioritize unchanged tiles


        if(tile1.scalable[BOTTOM] && tile1.area == tile1.area_past)
        {
            int cap = tile1.area.y + tile1.min_size.y;

            bool is_anchored = tile1.mandatory_area.x > 0 || tile1.mandatory_area.y > 0;
            if(is_anchored)
                cap = max(cap, tile1.mandatory_area.y + tile1.mandatory_area.h);

            // int dist_t;
            dist_t = min(debt, tile1.area.h + tile1.area.y - cap);
            tile1.area.h -= dist_t;
            debt -= dist_t;
        }

        if(tile2.scalable[TOP] && debt > 0)
        {
            int cap = tile2.area.y + tile2.area.h - tile2.min_size.y;

            bool is_anchored = tile2.mandatory_area.x > 0 || tile2.mandatory_area.y > 0;
            if(is_anchored)
                cap = min(cap, tile2.mandatory_area.y);

            // int dist_b;
            dist_b = min(debt, cap - tile2.area.y);
            tile2.area.y += dist_b;
            tile2.area.h -= dist_b;
            debt -= dist_b;
        }

        if(dist_t == -1 && tile1.scalable[BOTTOM] && debt > 0 && tile1.area != tile1.area_past)
        {
            int cap = tile1.area.y + tile1.min_size.y;

            bool is_anchored = tile1.mandatory_area.x > 0 || tile1.mandatory_area.y > 0;
            if(is_anchored)
                cap = max(cap, tile1.mandatory_area.y + tile1.mandatory_area.h);

            // int dist_t;
            dist_t = min(debt, tile1.area.h + tile1.area.y - cap);
            tile1.area.h -= dist_t;
            debt -= dist_t;
        }

        player.area.y = tile1.area.y + tile1.area.h;
        player.has_foothold = true;

        if(debt > 0)
        {
            cout << "Player got squished and couldn't figure what tile to shrink." << endl;
            cout << "Initial squish debt: " << _debt << endl;
            cout << "Top cushion used: " << dist_t << endl;
            cout << "Bottom cushion used: " << dist_b << endl;
            cout << "Leftover debt: " << debt << endl;
            cout << "Above info is not very useful. Attach video and description, please." << endl;
        }
    }
    else if(roof.size() && roof[0].dist < 0)
    {
        // A little easter egg :)
        // Sadly, i don't think i'll have time to implement similar stuff in the other directions
        // Though it can be a lot of fun to play with this mechanic.
        //player.velocity.y = max(0.0f, -1.0f * roof[0].dist / ms);
        //
        // Note: I had to commend that one out because it was acting strange on some occasions
        // For example, when you horizontally squash a player who's falling with a wall that's
        // got small enough height to activate the vertical motion, the player just storms down.
        if(player.velocity.y < 0.0f)
            player.velocity.y = 0.0f;
        player.area.y += -roof[0].dist;
    }
    else if(floor.size() && floor[0].dist <= 0)
    {
        player.area.y -= -floor[0].dist;

        if(player.velocity.y >= 0) // Don't mess with jumps
            player.has_foothold = true;
    }

    if(false)
    {
        cout << "roof: ";
        for(auto a : roof) {
            cout << a.dist << " ";
        }
        cout << endl;
        cout << "floor: ";
        for(auto a : floor) {
            cout << a.dist << " ";
        }
        cout << endl;
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
    }
}

