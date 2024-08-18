#ifndef INCLUDE_WE_DATA_HPP
#define INCLUDE_WE_DATA_HPP

#include "world/data.hpp"

namespace WE
{
    struct MouseFocus
    {
        int level = -1;
        Rect area;
        Point pos;

        bool dragging = false;
    };

    extern MouseFocus mouse_focus;
}

#endif // INCLUDE_WE_DATA_HPP
