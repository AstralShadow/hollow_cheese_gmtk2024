#ifndef INCLUDE_GAME_OBJECT_HPP
#define INCLUDE_GAME_OBJECT_HPP

#include "utils/point.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

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
    };

    extern vector<Object> objects;


    void init_objects();
    Object* object(string name);
}

#endif // INCLUDE_GAME_OBJECT_HPP
