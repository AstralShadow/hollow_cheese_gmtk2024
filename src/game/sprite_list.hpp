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
        // World Editor
        { BASE "buttons/plus.png",              "create"},
        { BASE "buttons/edit-2.png",              "edit"},
        { BASE "buttons/copy.png",              "copy"},
        { BASE "buttons/delete.png",            "delete"},


        // Level Editor
        { BASE "buttons/play.png",              "simulation"},
        { BASE "buttons/players.png",           "player_count"},
        { BASE "buttons/jump-prediction.png",   "jump_prediction"},
        { BASE "buttons/pause.png",             "time_pause"},
        { BASE "buttons/slow-motion.png",       "slow_motion"},

        { BASE "buttons/edit-mode.png",         "edit_mode"},
        { BASE "buttons/texture-mode.png",      "texture_mode"},
        { BASE "buttons/object-mode.png",       "object_mode"},

        { BASE "buttons/exit.png",              "exit"},
    };
}

#else // INCLUDE_GAME_SPRITE_LIST_HPP

#pragma message("game/sprite_list.hpp shuold be included only once in total.")

#endif // INCLUDE_GAME_SPRITE_LIST_HPP
