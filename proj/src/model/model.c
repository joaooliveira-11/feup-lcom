#include "model.h"

extern uint8_t scancode;
extern uint8_t mouse_byte_index; 
SystemState systemstate = ON;
GameState gamestate = START_MENU;
extern vbe_mode_info_t vbe_mode_info;
extern mouse_t mouse_packet;

sprite_t *mouse;
sprite_t *button1;
sprite_t *button2;
sprite_t *button3;
sprite_t *button4;
sprite_t *initial_screen_background;
sprite_t *instructions_screen;
sprite_t *play_button;
sprite_t *quit_button;
sprite_t *inst_button;
sprite_t *multi_button;
sprite_t *back_button;

void create_mouse_sprite(){
    mouse = sprite_build((xpm_map_t) mouse_xpm);
}

void create_menu_sprites(){
    initial_screen_background = sprite_build((xpm_map_t) background_final_xpm);
    set_sprite_xpos(initial_screen_background, 0);
    set_sprite_ypos(initial_screen_background, 0);
}
void create_menu_buttons(){

    play_button = sprite_build((xpm_map_t) button_play_xpm);
    set_sprite_xpos(play_button, 35);
    set_sprite_ypos(play_button, 235);

    quit_button = sprite_build((xpm_map_t) button_quit_xpm);
    set_sprite_xpos(quit_button, 560);
    set_sprite_ypos(quit_button, 365);

    inst_button = sprite_build((xpm_map_t) button_inst_xpm);
    set_sprite_xpos(inst_button, 35);
    set_sprite_ypos(inst_button, 365);

    multi_button = sprite_build((xpm_map_t) button_multi_xpm);
    set_sprite_xpos(multi_button, 560);
    set_sprite_ypos(multi_button, 235);
}

void create_instructions_sprites(){
    instructions_screen = sprite_build((xpm_map_t) instructions_xpm);
    set_sprite_xpos(instructions_screen, 0);
    set_sprite_ypos(instructions_screen, 0);
}
void create_instructions_buttons(){
    back_button = sprite_build((xpm_map_t) button_back_xpm);
    set_sprite_xpos(back_button, 607);
    set_sprite_ypos(back_button, 495);
}

//void create_game_sprites();
void create_game_buttons(){
    button1 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, ORANGE);
    button2 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, BLUE);
    button3 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, GREEN);
    button4 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, YELLOW);
}

void delete_mouse_sprite(){
    sprite_delete(mouse);
}

void delete_menu_sprites(){
    sprite_delete(initial_screen_background);
}
void delete_menu_buttons(){
    sprite_delete(play_button);
    sprite_delete(quit_button);
    sprite_delete(inst_button);
    sprite_delete(multi_button);
}

void delete_instructions_sprites(){
    sprite_delete(instructions_screen);
}
void delete_instructions_buttons(){
    sprite_delete(back_button);
}

//void delete_game_sprites();
void delete_game_buttons(){
    sprite_delete(button1);
    sprite_delete(button2);
    sprite_delete(button3);
    sprite_delete(button4);
}

void update_timer() {
    if (ACTIVE_DOUBLE_Buffer) buffer_swap();
}

void update_keyboard() {
    (kbc_ih)();
    switch (scancode) {
        case QUIT:
            systemstate = OFF;
            break;
        case INITIAL_MENU:
            gamestate = START_MENU;
            break;
        case GAME_SCREEN:
            gamestate = PLAYING;
            break;
        default:
            break;
    }
    draw_frame();
}

void update_mouse(){
    mouse_ih();
    mouse_sync_bytes();
    if(mouse_byte_index == 3){
        mouse_bytes_to_packet();
        draw_frame();
        check_mouse_clicks();
        mouse_byte_index = 0;
    }
}
