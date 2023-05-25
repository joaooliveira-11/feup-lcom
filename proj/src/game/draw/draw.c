#include "draw.h"

uint8_t *first_frame_buffer;
uint8_t *second_frame_buffer;
uint32_t frame_buffer_size;

extern vbe_mode_info_t vbe_mode_info;
extern mouse_t mouse_packet;
extern struct gamecontext context;


int allocate_double_buffer(uint16_t mode) {
    if (frame_buffer_build(mode, &first_frame_buffer)) return 1;
    frame_buffer_size = vbe_mode_info.XResolution * vbe_mode_info.YResolution * ((vbe_mode_info.BitsPerPixel + 7) / 8);
    second_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
    return 0;
}

void update_buffers() {
    memcpy(first_frame_buffer, second_frame_buffer, frame_buffer_size);
}


int draw_movingSprite_xpm(sprite_t *sprite) { 
    uint16_t sprite_xpos = get_sprite_xpos(sprite);
    uint16_t sprite_ypos = get_sprite_ypos(sprite);
    uint32_t current_color;
    for (int y = 0 ; y < sprite->height ; y++) {
      for (int x = 0 ; x < sprite->width ; x++) {
        current_color = sprite->colors_array[x + y*sprite->width];
        if (current_color == TRANSPARENT) continue;
        if (color_pixel(sprite_xpos + x, sprite_ypos + y, current_color, second_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}

int draw_staticSprite_xpm(sprite_t *sprite, uint16_t x, uint16_t y) { 
    uint16_t sprite_xpos = x;
    uint16_t sprite_ypos = y;
    uint32_t current_color;
    for (int y = 0 ; y < sprite->height ; y++) {
      for (int x = 0 ; x < sprite->width ; x++) {
        current_color = sprite->colors_array[x + y*sprite->width];
        if (current_color == TRANSPARENT) continue;
        if (color_pixel(sprite_xpos + x, sprite_ypos + y, current_color, second_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}

void draw_map(){
    for (int i = 0; i < context.numWalls; i++) {
        uint16_t xPos = context.walls[i].x;
        uint16_t yPos = context.walls[i].y;
        draw_staticSprite_xpm(context.wall, xPos, yPos);
    }
}

void draw_frame() {
    if(context.quit_button->is_pressed){
        context.gamestatus = OFF;
        return;
    }
    if(context.play_button->is_pressed) context.gamestate = PLAYING;
    if(context.inst_button->is_pressed) context.gamestate = INSTRUCTIONS_MENU;
    if(context.back_button->is_pressed) context.gamestate = START_MENU;

    switch (context.gamestate) {
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
    draw_staticSprite_xpm(context.initial_screen_background, 0,0);
    draw_staticSprite_xpm(context.play_button,35,235);
    draw_staticSprite_xpm(context.quit_button,560,365);
    draw_staticSprite_xpm(context.inst_button,35,365);
    draw_staticSprite_xpm(context.multi_button,560,235);
}

void draw_instructions_menu_screen() {
    draw_staticSprite_xpm(context.instructions_screen,0,0);
    draw_staticSprite_xpm(context.back_button, 607,495);
}


void draw_game_screen(){
    draw_staticSprite_xpm(context.game_screen,0,0);
    draw_map();
    draw_movingSprite_xpm(context.boy);
    draw_movingSprite_xpm(context.girl);
}

void draw_newMouse_pos(){
    set_sprite_xpos(context.mouse, mouse_packet.xpos);
    set_sprite_ypos(context.mouse, mouse_packet.ypos);
    draw_movingSprite_xpm(context.mouse);
}
