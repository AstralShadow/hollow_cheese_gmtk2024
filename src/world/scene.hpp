#ifndef INCLUDE_WORLD_SCENE_HPP
#define INCLUDE_WORLD_SCENE_HPP

/// This one's meant for data keeping and rendering functions

namespace world
{
    struct scene_uid_t;
    typedef struct scene_uid_t* scene_uid;

    void init(int, char**, scene_uid = 0);
    void deinit(scene_uid = 0);
}

#endif // INCLUDE_WORLD_SCENE_HPP
