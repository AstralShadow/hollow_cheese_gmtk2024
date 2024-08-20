#include "game/sprite.hpp"
#include "game/sprite_list.hpp"
#include "utils/textures.hpp"
#include <map>
#include <iostream>
#include <SDL2/SDL_timer.h>

using std::cout;
using std::endl;

using utils::load_surface;
using utils::create_texture;

static std::map<string, SDL_Texture*(*)(string const&)> _texture_accessor;
static std::map<string, SDL_Texture*> _textures;
static std::map<SDL_Texture*, Point> _size;
static std::map<SDL_Texture*, Point> _offset;


SDL_Texture* game::sprite(string path)
{
    auto itr = _texture_accessor.find(path);
    if(itr != _texture_accessor.end())
        return itr->second(path);

    auto itr2 = _textures.find(path);
    if(itr2 != _textures.end())
        return itr2->second;

    //cout << "Could not find texture '" << path << "'" << endl;
    return nullptr;
}

Point game::sprite_size(SDL_Texture* texture)
{
    if(texture == nullptr)
        return {0, 0};

    auto itr = _size.find(texture);
    if(itr == _size.end())
        return {0, 0};

    return itr->second;
}

Point game::sprite_offset(SDL_Texture* texture)
{
    if(texture == nullptr)
        return {0, 0};

    auto itr = _offset.find(texture);
    if(itr == _offset.end())
        return {0, 0};

    return itr->second;
}


void game::init_sprites()
{
    for(auto const& data : sprite_data)
    {
        if(data.path != "")
            cout << "Loading sprite '" << data.path << "'." << endl;
        else
            cout << "Registering sprite '" << data.alias << "'." << endl;

        if(data.path != "")
        {
            auto surf = load_surface(data.path);
            auto tex = create_texture(surf);

            _size[tex] = {surf->w, surf->h};
            _offset[tex] = data.offset;
            cout << "size: " << surf->w << ' ' << surf->h << " \t";
            cout << "offset: " << data.offset.x << ' ' << data.offset.y << endl;

            SDL_FreeSurface(surf);

            if(data.path != "")
                _textures[data.path] = tex;

            if(data.alias != "")
                _textures[data.alias] = tex;
        }


        if(data.get_texture)
        {
            if(data.path != "")
                _texture_accessor[data.path] = data.get_texture;

            if(data.alias != "")
                _texture_accessor[data.alias] = data.get_texture;
        }
    }
}


/* Animation */

template<int frames> static
SDL_Texture* animated_texture(string const& name)
{
    const int framerate = 9;
    size_t frame = SDL_GetTicks() / (1000 / framerate);

    string frame_name = name + "-" + std::to_string(frame % frames);
    return game::sprite(frame_name);
}

SDL_Texture* game::animated_texture_7(string const& name)
{
    return animated_texture<7>(name);
}

SDL_Texture* game::animated_texture_11(string const& name)
{
    return animated_texture<11>(name);
}

