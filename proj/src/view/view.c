#include "view.h"

uint8_t *first_frame_buffer;
uint8_t *second_frame_buffer;
uint8_t *active_buffer;
uint32_t frame_buffer_size;
extern vbe_mode_info_t vbe_mode_info;
extern GameState gamestate;

extern sprite_t *mouse;
extern sprite_t *button1;
extern sprite_t *button2;
extern sprite_t *button3;
extern sprite_t *button4;
extern sprite_t *play_button;
extern sprite_t *quit_button;
extern sprite_t *inst_button;
extern sprite_t *multi_button;
extern sprite_t *initial_screen_background;


int build_buffers(uint16_t mode) {
    if (frame_buffer_build(mode, &first_frame_buffer)) return 1;
    frame_buffer_size = vbe_mode_info.XResolution * vbe_mode_info.YResolution * ((vbe_mode_info.BitsPerPixel + 7) / 8);
    if (ACTIVE_DOUBLE_Buffer) {
        second_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
        active_buffer = second_frame_buffer;
    } else {
        active_buffer =first_frame_buffer;
    }
    return 0;
}

void buffer_swap() {
    memcpy(first_frame_buffer, second_frame_buffer, frame_buffer_size);
}

void draw_frame() {
    switch (gamestate) {
        case START_MENU:
            draw_initial_menu_screen();
            break;
        case PLAYING:
            draw_game_screen();
            break;
    }
}

void draw_initial_menu_screen() {
    draw_sprite_xpm(initial_screen_background, 0, 0);
    draw_sprite_xpm(play_button, 35, 235);
    draw_sprite_xpm(quit_button, 560, 365);
    draw_sprite_xpm(inst_button, 35, 365);
    draw_sprite_xpm(multi_button, 560, 235);
}

void draw_game_screen(){
    draw_sprite_button(button1, 0, 0);
    draw_sprite_button(button2, vbe_mode_info.XResolution/2, 0);
    draw_sprite_button(button3, 0, vbe_mode_info.YResolution/2);
    draw_sprite_button(button4, vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2);
}

int draw_sprite_xpm(sprite_t *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t current_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        current_color = sprite->colors_array[w + h*width];
        if (current_color == TRANSPARENT) continue;
        if (color_pixel(x + w, y + h, current_color, active_buffer) != 0) return 1;
      }
    }
    return 0; 
}

int draw_sprite_button(sprite_t *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color = sprite->is_pressed ? MOUSE_PRESS : sprite->main_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        if (color_pixel(x + w, y + h, color, active_buffer) != 0) return 1;
      }
    }
    return 0; 
}