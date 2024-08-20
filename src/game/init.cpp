#include "game/game.hpp"
#include "game/data.hpp"
#include "game/sprite.hpp"
#include "game/object.hpp"
#include <iostream>

using std::cout;
using std::endl;


namespace game
{
    vector<Player> players {
        Player{
            .area = {0, 200, 32, 64}
        }/*,
        {
            .area = {128, 200, 32, 64},
            .controls = {
                SDL_SCANCODE_UP,
                SDL_SCANCODE_RIGHT,
                SDL_SCANCODE_DOWN,
                SDL_SCANCODE_LEFT
            }
        }*/
    };

    bool enable_level_editor = false;
    Button level_editor_btn = {
        Point {8, WINDOW_HEIGHT - 40},
        "Open in Level Editor",
        &open_level_editor,
        "edit"
    };
}


void game::init(int, char**, scene_uid)
{
    init_sprites();
    init_objects();
    generate_button_label(level_editor_btn);

    pick_first_level();
    position_players_near("game_start_point");
}

void game::deinit(scene_uid)
{

}


void game::pick_first_level()
{
    const string start_point = "game_start_point";

    vector<size_t> starts;

    for(size_t i = 0; i < world.levels.size(); i++)
    {
        auto const& objects = world.levels[i].level.objects;
        for(auto const& o : objects)
            if(o.name == start_point)
            {
                starts.push_back(i);
                break;
            }
    }

    if(starts.size() == 0)
    {
        cout << "No start level found" << endl;
        return;
    }

    if(starts.size() > 1)
        cout << "Multiple start levels found. Picking first one." << endl;

    world.current_level = starts[0];
}

void game::position_players_near(string target, int prev_level)
{
    Point pick {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    if(world.current_level < world.levels.size())
    {
        vector<Point> options;

        auto const& objects = world.levels[world.current_level].level.objects;
        for(auto const& o : objects)
            if(o.name == target)
                options.push_back(o.pos);

        /* Pick best option */
        {
            if(options.size() > 1 && prev_level != -1)
            {
                Point new_p = world.levels[world.current_level].pos;
                Point old_p = world.levels[prev_level].pos;
                Point delta = old_p - new_p;

                bool first = false;
                int _pick = 0;
                int dist2 = 0;
                for(size_t i = 0; i < options.size(); ++i)
                {
                    Point d = delta + objects[i].pos;
                    int _dist2 = d.x * d.x + d.y * d.y;
                    if(first || dist2 > _dist2)
                    {
                        // TODO use player position too.
                        dist2 = _dist2;
                        _pick = i;
                        first = false;
                    }
                }

                pick = options[_pick]; // TODO fix variable names
            }
            else if(!options.empty())
                pick = options[0];
        }
    }

    int w = 0;
    for(size_t i = 0; i < players.size(); i++)
    {
        auto& p = players[i];
        p.area.x = pick.x + w;
        p.area.y = pick.y;
        p.velocity.y = 0;

        w += p.area.w + 8;
    }
}
