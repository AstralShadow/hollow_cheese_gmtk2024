#ifndef INCLUDE_WE_DATA_HPP
#define INCLUDE_WE_DATA_HPP

#include "world/data.hpp"
#include "game/button.hpp"
#include <vector>

using std::vector;


namespace WE
{
    struct MouseFocus
    {
        int level = -1;
        Rect area;
        Point pos;

        bool dragging = false;
        bool selected = false;
    };

    extern MouseFocus mouse_focus;


    using game::Button;
    using game::button_size;
    using game::generate_button_label;
    using game::render_button;
    using game::render_button_label;
    extern vector<Button> level_buttons;
    extern vector<Button> global_buttons;

    Button* button_on_pos(Point pos);
    bool click_button(Point pos);


    void render_level_tool_overlay();

    void render_level_button(Button const&);
    void render_global_button(Button const&);


    void new_level();
    void edit_level();
    void clone_level();
    void delete_level();
}

#endif // INCLUDE_WE_DATA_HPP
