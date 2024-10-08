#ifndef INCLUDE_LE_DATA_HPP
#define INCLUDE_LE_DATA_HPP

#include "utils/types.hpp"
#include "world/data.hpp"
#include "game/player.hpp"
#include "game/button.hpp"

namespace LE
{
    using world::Level;

    extern int target_level;
    Level* level();


    struct PlayerData
    {
        // bool keep_displaying_jump_reach = false;
        bool dragging = false;
        bool plan_to_drop = false; // Don't drop within collidable area
        Point drag_offset {0, 0};
    };

    using game::Player;
    extern vector<Player> players; // Mock player objects
    extern vector<PlayerData> players_data;
    extern int active_players; // I don't want to touch the vector above, it contains controllers
    extern int jump_prediction; // 0 - none; 1 - always; 2 - nearby. Reverse as UI lacks feedback

    extern bool time_pause;
    extern bool slow_motion;
    constexpr int slow_motion_factor = 5;

    extern bool creating_tile;
    extern Point drag_start;
    extern Point drag_buffer;
    extern bool modifying_tile_scalable_sides; // When editing tile but release before any drag
    extern bool drag_remove;
    using world::drag_target; // edit mode

    extern int drag_index; // object mode
    extern string drag_texture; // texture

    extern string last_action_error;

    enum mode_t
    {
        EDIT_MODE, // where you can edit the tiles' initial positions
        OBJECT_MODE, // where you add interactable objects
        TEXTURE_MODE, // where you can add textures to different z-layers
        // TEXT_MODE // where you add tutorial stuff
    } extern mode;


    /* Rendering */

    void render_levels(); // Rendered at 80% from screen
    Point get_level_coordinates(Point screen_pos);

    void render_player_overlays(float scale); // Calls SDL_RenderSetScale internally

    // May use Level to add snap hints.. tho not yet
    void render_grid(Level const&, float scale = 1);

    void render_buttons();

    void render_error_message();


    constexpr Rect menu_area {
        32 + WINDOW_WIDTH * 4 / 5 + 16,
        16,
        WINDOW_WIDTH - (32 + WINDOW_WIDTH * 4 / 5 + 16) - 16,
        WINDOW_HEIGHT - 16 - 16
    };
    extern int menu_scroll;
    extern int menu_content_height; // Update when rendering
    struct MenuZone
    {
        Rect area;
        size_t index;
    };
    extern vector<MenuZone> menu_zones; // Used for click detection

    void render_object_mode_menu();
    void render_texture_mode_menu();


    /* Features */
    bool start_dragging_player_under_cursor(Point cursor);
    void drag_players(Point cursor);
    void drop_dragged_players();

    bool start_modifying_tiles(Point cursor);
    void drag_tiles(Point pos, Point rel = {0, 0});
    void stop_modifying_tiles(Point cursor);
    void remove_tile(Point cursor);

    bool object_pick(Point cursor);
    void object_drag(Point cursor);
    void object_drop(Point cursor);
    void object_remove(Point cursor);

    bool texture_pick(Point cursor);
    void texture_drag(Point cursor);
    void texture_drop(Point cursor);
    void texture_remove(Point cursor);

    /* User interface */

    using game::Button;
    using game::button_size;
    using game::generate_button_label;
    using game::render_button;
    using game::render_button_label;
    extern vector<Button> buttons, mode_buttons;

    Button* button_on_pos(Point pos);
    bool click_button(Point pos);

    MenuZone* zone_on_pos(Point pos);
    bool click_zone(Point pos);

    bool click_zone_object_mode(size_t index);
    bool click_zone_texture_mode(size_t index);


    /* Actions */

    void play_level();
    void toggle_player_count(int count);
    inline void toggle_player_count() { toggle_player_count(-1); }
    void toggle_jump_prediction();

    void toggle_slow_motion();
    void toggle_time_pause();

    void set_edit_mode();
    void set_object_mode();
    void set_texture_mode();

    void open_world_editor();
}

#endif // INCLUDE_LE_DATA_HPP
