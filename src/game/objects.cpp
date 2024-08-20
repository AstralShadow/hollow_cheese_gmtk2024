#include "game/object.hpp"
#include <map>
#include <iostream>

using std::cout;
using std::endl;
using game::Object;

namespace game
{
    vector<Object> objects = {
        {"game_start_point", "", "", {64, 64},
            "Players spawn here when the game starts."},
        {"level_spawn_point", "", "", {64, 64},
            "Players spawn here when transitioning betwenn levels."}
    };

    static std::map<string, Object*> _index;
}


void game::init_objects()
{
    for(auto& obj : objects)
    {
        auto const& name = obj.name;
        if(object(name))
            cout << "Overwriting object '" << name << "'" << endl;
        _index[name] = &obj;
    }
}

Object* game::object(string name)
{
    auto itr = _index.find(name);
    if(itr == _index.end()) {
        cout << "No object with name '" << name << "'" << endl;
        return nullptr;
    }

    return itr->second;
}
