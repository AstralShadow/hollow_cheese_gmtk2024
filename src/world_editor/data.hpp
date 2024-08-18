#ifndef INCLUDE_WE_DATA_HPP
#define INCLUDE_WE_DATA_HPP

#include "world/data.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;

struct SDL_Texture;


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


    constexpr Point button_size = {32, 32};
    struct Button
    {
        Point pos;
        string label;
        void(*action)() = nullptr;

        bool focused = false; // Rendering data

        SDL_Texture* label_texture = nullptr; // Cache
        Point label_size {0, 0};
    };

    extern vector<Button> level_buttons;
    extern vector<Button> global_buttons;

    Button* button_on_pos(Point pos);
    bool click_button(Point pos);


    void render_level_tool_overlay();

    void render_level_button(Button const&);
    void render_global_button(Button const&);

    void generate_button_label(Button&);


    void new_level();
    void edit_level();
    void clone_level();
    void delete_level();
}

#endif // INCLUDE_WE_DATA_HPP
