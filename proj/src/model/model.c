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
sprite_t *game_screen;
sprite_t *boy;
sprite_t *girl;
sprite_t *boy_left;
sprite_t *boy_right;
sprite_t *girl_left;
sprite_t *girl_right;

void create_mouse_sprite(){
    mouse = sprite_build((xpm_map_t) mouse_xpm);
}

void create_menu_sprites(){
    initial_screen_background = sprite_build((xpm_map_t) background_final_xpm);
}

void create_menu_buttons(){
    play_button = sprite_build((xpm_map_t) button_play_xpm);
    quit_button = sprite_build((xpm_map_t) button_quit_xpm);
    inst_button = sprite_build((xpm_map_t) button_inst_xpm);
    multi_button = sprite_build((xpm_map_t) button_multi_xpm);
}

void create_instructions_sprites(){
    instructions_screen = sprite_build((xpm_map_t) instructions_xpm);
}

void create_instructions_buttons(){
    back_button = sprite_build((xpm_map_t) button_back_xpm);
}

void create_game_sprites(){
    game_screen = sprite_build((xpm_map_t) game_backgroung_xpm);

    boy = sprite_build((xpm_map_t) fireboy_xpm);
    set_sprite_xpos(boy, 35);
    set_sprite_ypos(boy, 235);

    girl = sprite_build((xpm_map_t) watergirl_xpm);
    set_sprite_xpos(girl, 35);
    set_sprite_ypos(girl, 365);

    boy_left = sprite_build((xpm_map_t) running_left_boy_xpm);
    boy_right = sprite_build((xpm_map_t) running_right_boy_xpm);
    girl_left = sprite_build((xpm_map_t) running_left_girl_xpm);
    girl_right = sprite_build((xpm_map_t) running_right_girl_xpm); 
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

void delete_game_sprites(){
    sprite_delete(game_screen);
    sprite_delete(boy);
    sprite_delete(boy_left);
    sprite_delete(boy_right);
    sprite_delete(girl_left);
    sprite_delete(girl_right);
    sprite_delete(girl);
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
