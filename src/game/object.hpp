#ifndef INCLUDE_GAME_OBJECT_HPP
#define INCLUDE_GAME_OBJECT_HPP

#include "utils/point.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

struct SDL_Texture;

namespace world { struct Level; }

namespace game
{
    struct Object
    {
        string name; // in level editor
        string label;
        string sprite; // may be animated
        Point size;
        string info; // in level editor

        void (*action)(world::Level& level, int object_id) = nullptr; // pick up action

        // Cache
        SDL_Texture* _name = nullptr;
        Point _name_size = {0, 0};
        SDL_Texture* _label = nullptr;
        Point _label_size = {0, 0};
        SDL_Texture* _info = nullptr;
        Point _info_size = {0, 0};
    };

    extern vector<Object> objects;


    void init_objects();
    Object* object(string name);

    void render_object(Object const* object, Point pos, float scale = 1, bool debug = false);
}

#endif // INCLUDE_GAME_OBJECT_HPP
