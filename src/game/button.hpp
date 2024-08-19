#ifndef INCLUDE_BUTTON_HPP
#define INCLUDE_BUTTON_HPP

#include "utils/point.hpp"
#include <string>

using std::string;

struct SDL_Texture;

namespace game
{
    struct Button
    {
        Point pos;
        string label;
        void(*action)() = nullptr;

        bool focused = false; // Rendering data

        SDL_Texture* label_texture = nullptr; // Cache
        Point label_size {0, 0};
    };

    void generate_button_label(Button&);

    void render_button(Button const& btn, Rect const& area);
    void render_button_label(Button const& btn, Point const& label_pos);
    void render_button_label(Button const& btn, Rect const& label_area);

    inline void render_button_with_label(Button const& btn, Rect const& area,
                                                            Rect const& label_area)
    {
        render_button(btn, area);
        render_button_label(btn, label_area);
    }

    inline void render_button_with_label(Button const& btn, Rect const& area,
                                                            Point const& label_pos)
    {
        render_button(btn, area);
        render_button_label(btn, label_pos);
    }
}

#endif // INCLUDE_BUTTON_HPP
