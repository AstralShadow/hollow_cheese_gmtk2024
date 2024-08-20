#include "game/object.hpp"
#include "utils/textures.hpp"
#include "game/fonts.hpp"
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

struct RenderTextAnswer
{
    SDL_Texture* ptr;
    Point size;
};

static RenderTextAnswer render_text(string text, SDL_Color color)
{
    auto font = game::get_font();

    auto surf = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, 0);
    if(!surf) {
        cout << "Failed to render text" << endl;
        cout << TTF_GetError() << endl;
        return {nullptr, {0, 0}};
    }

    RenderTextAnswer answer {
        utils::create_texture(surf),
        Point{ surf->w, surf->h }
    };

    SDL_FreeSurface(surf);

    return answer;
}

void game::init_objects()
{
    cout << "Initializing objects..." << endl;

    for(auto& obj : objects)
    {
        auto const& name = obj.name;
        if(object(name))
            cout << "Overwriting object '" << name << "'" << endl;
        _index[name] = &obj;

        /* Texture cache */
        {
            const SDL_Color color {0x98, 0xd2, 0xff, 255};

            auto name = render_text(obj.name, color);
            obj._name = name.ptr;
            obj._name_size = name.size;

            auto label = render_text(obj.label, color);
            obj._label = label.ptr;
            obj._label_size = label.size;

            auto info = render_text(obj.info, color);
            obj._info = info.ptr;
            obj._info_size = info.size;
        }
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
