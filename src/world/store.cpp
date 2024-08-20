#include "world/data.hpp"
#include "storage/utils.hpp"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

using world::World;

using namespace storage;

#define WORLD_FILE "assets/world.bin"


namespace world
{
    static void load_world_1(istream& blob, World&);
    #ifndef __EMSCRIPTEN__
        static void save_world_1(World const&, ostream& blob);
    #endif
}


void world::save_world()
{
#ifndef __EMSCRIPTEN__
    std::ofstream file(WORLD_FILE);
    if(!file)
        cout << "Could not save world: " << WORLD_FILE << endl;
    else
        save_world_1(world, file);
#endif // __EMSCRIPTEN__
}

void world::load_world()
{
    std::ifstream file(WORLD_FILE);
    if(!file)
        cout << "Could not load world: " << WORLD_FILE << endl;
    else
        load_world_1(file, world);
}


#ifndef __EMSCRIPTEN__

void world::save_world_1(World const& world, ostream& blob)
{
    write8(blob, 1);

    write8(blob, world.levels.size());
    for(auto const& level : world.levels)
    {
        write32(blob, level.pos.x);
        write32(blob, level.pos.y);

        write32(blob, level.level.tiles.size());
        write32(blob, level.level.objects.size());
        write32(blob, level.level.textures.size());

        for(auto const& t : level.level.tiles)
        {
            write32(blob, t.original_area.x);
            write32(blob, t.original_area.y);
            write32(blob, t.original_area.w);
            write32(blob, t.original_area.h);

            write32(blob, t.min_size.x);
            write32(blob, t.min_size.y);

            write32(blob, t.mandatory_area.x);
            write32(blob, t.mandatory_area.y);
            write32(blob, t.mandatory_area.w);
            write32(blob, t.mandatory_area.h);

            write8(blob, t.scalable[0]);
            write8(blob, t.scalable[1]);
            write8(blob, t.scalable[2]);
            write8(blob, t.scalable[3]);
        }

        for(auto const& o : level.level.objects)
        {
            write32(blob, o.pos.x);
            write32(blob, o.pos.y);
            write(blob, o.name);
        }

        for(auto const& t : level.level.textures)
        {
            write32(blob, t.pos.x);
            write32(blob, t.pos.y);
            write(blob, t.name);
        }
    }
}

#endif // __EMSCRIPTEN__

void world::load_world_1(istream& blob, World& world)
{
    if(read8(blob) != 1)
    {
        cout << "Incorrect world version." << endl;
        return;
    }

    world.levels.clear();
    int lvl_cnt = read8(blob);

    for(int l = 0; l < lvl_cnt; l++)
    {
        Point pos;
        pos.x = read32(blob);
        pos.y = read32(blob);

        int tiles = read32(blob);
        int objects = read32(blob);
        int textures = read32(blob);

        Level level;

        for(int i = 0; i < tiles; i++)
        {
            Rect area;
            area.x = read32(blob);
            area.y = read32(blob);
            area.w = read32(blob);
            area.h = read32(blob);

            Point min_size;
            min_size.x = read32(blob);
            min_size.y = read32(blob);

            Rect mand;
            mand.x = read32(blob);
            mand.y = read32(blob);
            mand.w = read32(blob);
            mand.h = read32(blob);

            Tile tile {
                .area = area,
                .min_size = min_size,
                .mandatory_area = mand
            };

            for(int i = 0; i < 4; i++)
                tile.scalable[i] = read8(blob);

            level.tiles.push_back(tile);
        }

        for(int i = 0; i < objects; ++i)
        {
            Point pos;
            pos.x = read32(blob);
            pos.y = read32(blob);
            string name = read(blob);

            level.objects.push_back({
                .name = name,
                .pos = pos
            });
        }


        for(int i = 0; i < textures; ++i)
        {
            Point pos;
            pos.x = read32(blob);
            pos.y = read32(blob);
            string name = read(blob);

            level.textures.push_back({
                .name = name,
                .pos = pos
            });
        }

        world.levels.push_back({
            .level = level,
            .pos = pos
        });
    }
}
