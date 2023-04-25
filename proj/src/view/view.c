#include "view.h"

uint8_t *first_frame_buffer;
uint8_t *second_frame_buffer;
uint8_t *active_buffer;
uint32_t frame_buffer_size;
extern vbe_mode_info_t vbe_mode_info;
extern GameState gamestate;
extern SystemState systemstate;
extern mouse_t mouse_packet;
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
extern sprite_t *instructions_screen;
extern sprite_t *back_button;


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
    if(quit_button->is_pressed){
        systemstate = OFF;
        return;
    }
    if(play_button->is_pressed) gamestate = PLAYING;
    if(inst_button->is_pressed) gamestate = INSTRUCTIONS_MENU;
    if(back_button->is_pressed) gamestate = START_MENU;

    switch (gamestate) {
        case START_MENU:
            draw_initial_menu_screen();
            break;
        case PLAYING:
            draw_game_screen();
            break;
        case INSTRUCTIONS_MENU:
            draw_instructions_menu_screen();
            break;
    }
    draw_newMouse_pos();
}

void draw_initial_menu_screen() {
    draw_sprite_xpm(initial_screen_background, 0, 0);
    draw_sprite_xpm(play_button, 35, 235);
    draw_sprite_xpm(quit_button, 560, 365);
    draw_sprite_xpm(inst_button, 35, 365);
    draw_sprite_xpm(multi_button, 560, 235);
}

void draw_instructions_menu_screen() {
    draw_sprite_xpm(instructions_screen, 0, 0);
    draw_sprite_xpm(back_button, 607, 495);
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

void draw_newMouse_pos(){
    draw_sprite_xpm(mouse, mouse_packet.xpos, mouse_packet.ypos);
}

void check_mouse_clicks(){
    if(mouse_packet.lb){
        switch(gamestate) {
            case START_MENU:{
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 235 && mouse_packet.ypos <= 332){
                    play_button->is_pressed = 1;
                }
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    inst_button->is_pressed = 1;
                }
                if(mouse_packet.xpos >= 560 && mouse_packet.xpos <= 760 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    quit_button->is_pressed = 1;
                }
                break;
            }
            case INSTRUCTIONS_MENU:
                if(mouse_packet.xpos >= 607 && mouse_packet.xpos <= 777 && mouse_packet.ypos >= 495 && mouse_packet.ypos <= 577){
                  back_button->is_pressed = 1;
                }  
                break;   
            default:
                break;
        }
        
    }
    else{
        play_button->is_pressed = 0;
        quit_button->is_pressed = 0;
        inst_button->is_pressed = 0;
        back_button->is_pressed = 0;
    }
}
