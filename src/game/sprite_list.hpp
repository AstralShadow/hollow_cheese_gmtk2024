#ifndef INCLUDE_GAME_SPRITE_LIST_HPP
#define INCLUDE_GAME_SPRITE_LIST_HPP

#include <string>
#include <array>

using std::string;
using std::array;


namespace game
{
    struct SpriteData
    {
        string path;
        string alias = "";
    };

    #define BASE "assets/"

    SpriteData sprite_data[] { SpriteData
        { BASE "gmtk/gmtk2024-g.png" },

    };
}

#else // INCLUDE_GAME_SPRITE_LIST_HPP

#pragma message("game/sprite_list.hpp shuold be included only once in total.")

#endif // INCLUDE_GAME_SPRITE_LIST_HPP
