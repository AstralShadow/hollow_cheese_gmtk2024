#include "game/sprite.hpp"
#include "game/sprite_list.hpp"
#include "utils/textures.hpp"
#include <map>
#include <iostream>

using std::cout;
using std::endl;

using utils::load_surface;
using utils::create_texture;

static std::map<string, SDL_Texture*> textures;
static std::map<SDL_Texture*, Point> size;


SDL_Texture* game::sprite(string path)
{
    return textures[path];
}

Point game::sprite_size(SDL_Texture* texture)
{
    return size[texture];
}


void game::init_sprites()
{
    for(auto const& data : sprite_data)
    {
        cout << "Loading sprite '" << data.path << "'." << endl;

        auto surf = load_surface(data.path);
        auto tex = create_texture(surf);

        size[tex] = {surf->w, surf->h};

        textures[data.path] = tex;
        if(data.alias != "")
            textures[data.alias] = tex;

        SDL_FreeSurface(surf);
    }
}
