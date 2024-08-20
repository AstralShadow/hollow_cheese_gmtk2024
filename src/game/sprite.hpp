#ifndef INCLUDE_GAME_SPRITES_HPP
#define INCLUDE_GAME_SPRITES_HPP

#include "utils/point.hpp"
#include <string>

using std::string;

struct SDL_Texture;


namespace game
{
    SDL_Texture* sprite(string path); // may return specific frame

    Point sprite_size(SDL_Texture*);
    inline Point sprite_size(string path)
        { return sprite_size(sprite(path)); }

    Point sprite_offset(SDL_Texture*);
    inline Point sprite_offset(string path)
        { return sprite_offset(sprite(path)); }

    void init_sprites();
}

#endif // INCLUDE_GAME_SPRITES_HPP
