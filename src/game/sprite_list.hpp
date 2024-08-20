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
        string path = "";
        string alias = "";
        Point offset {0, 0};

        SDL_Texture* (*get_texture)(string const&) = nullptr; // Map texture to another one
    };


    // Custom texture determinators
    SDL_Texture* animated_texture_7(string const&);
    SDL_Texture* animated_texture_11(string const&);

    #define BASE "assets/"

    SpriteData sprite_data[] { SpriteData
        // World Editor
        { BASE "buttons/plus.png",              "create"},
        { BASE "buttons/edit-2.png",            "edit"},
        { BASE "buttons/copy.png",              "copy"},
        { BASE "buttons/delete.png",            "delete"},


        // Level Editor
        { BASE "buttons/play.png",              "play_level"},
        { BASE "buttons/players.png",           "player_count"},
        { BASE "buttons/jump-prediction.png",   "jump_prediction"},
        { BASE "buttons/pause.png",             "time_pause"},
        { BASE "buttons/slow-motion.png",       "slow_motion"},

        { BASE "buttons/edit-mode.png",         "edit_mode"},
        { BASE "buttons/texture-mode.png",      "texture_mode"},
        { BASE "buttons/object-mode.png",       "object_mode"},

        { BASE "buttons/exit.png",              "exit"},
        // TODO add text mode and help


        { BASE "ground/ground.png", "ground" },
        { BASE "ground/ground-wall-dark.png", "ground-wall-dark" },
        { BASE "ground/ground-lower-part.png", "ground-lower-part" },
        { BASE "ground/lower-part.png", "lower-part" },
        { BASE "ground/ground-middle-part.png", "ground-middle-part" },
        { BASE "ground/middle-part.png", "middle-part" },
        { BASE "ground/ground-full-part.png", "ground-full-part" },
        { BASE "ground/full-part.png", "full-part" },
        { BASE "ground/ground-wall-light.png", "ground-wall-light" },
        { BASE "ground/lower-part-right-end.png", "lower-part-right-end" },
        { BASE "ground/lower-part-left-end.png", "lower-part-left-end" },

        { BASE "decorations/top-decoration-double-deer.png", "top decoration double deer" },
        { BASE "decorations/top-decoration-holy-cheese.png", "top decoration holy cheese" },
        { .alias = "chain", .get_texture = &animated_texture_11 },
        { BASE "decorations/chains/chain-0001.png", "chain-0" },
        { BASE "decorations/chains/chain-0002.png", "chain-1" },
        { BASE "decorations/chains/chain-0003.png", "chain-2" },
        { BASE "decorations/chains/chain-0004.png", "chain-3" },
        { BASE "decorations/chains/chain-0005.png", "chain-4" },
        { BASE "decorations/chains/chain-0006.png", "chain-5" },
        { BASE "decorations/chains/chain-0007.png", "chain-6" },
        { BASE "decorations/chains/chain-0008.png", "chain-7" },
        { BASE "decorations/chains/chain-0009.png", "chain-8" },
        { BASE "decorations/chains/chain-0010.png", "chain-9" },
        { BASE "decorations/chains/chain-0011.png", "chain-10" },

        // Cheese (object
        { .alias = "cheese", .get_texture = &animated_texture_7 },
        { BASE "objects/cheese/chesse-0001.png", "cheese-0"},
        { BASE "objects/cheese/chesse-0002.png", "cheese-1"},
        { BASE "objects/cheese/chesse-0003.png", "cheese-2"},
        { BASE "objects/cheese/chesse-0004.png", "cheese-3"},
        { BASE "objects/cheese/chesse-0005.png", "cheese-4"},
        { BASE "objects/cheese/chesse-0006.png", "cheese-5"},
        { BASE "objects/cheese/chesse-0007.png", "cheese-6"},


        // Player
        { BASE "player/player-light.png", "player_background"}, // TODO center behind player
    };
}

#else // INCLUDE_GAME_SPRITE_LIST_HPP

#pragma message("game/sprite_list.hpp shuold be included only once in total.")

#endif // INCLUDE_GAME_SPRITE_LIST_HPP
