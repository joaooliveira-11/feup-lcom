#include "model.h"

extern uint8_t scancode;
SystemState systemstate = ON;
GameState gamestate = START_MENU;
extern vbe_mode_info_t vbe_mode_info;

sprite_t *mouse;
sprite_t *button1;
sprite_t *button2;
sprite_t *button3;
sprite_t *button4;
sprite_t *initial_screen_background;
sprite_t *play_button;
sprite_t *quit_button;
sprite_t *inst_button;
sprite_t *multi_button;

void prepare_sprites(){
    mouse = sprite_build((xpm_map_t) mouse_xpm);
    initial_screen_background = sprite_build((xpm_map_t) background_final_xpm);
    play_button = sprite_build((xpm_map_t) button_play_xpm);
    quit_button = sprite_build((xpm_map_t) button_quit_xpm);
    inst_button = sprite_build((xpm_map_t) button_inst_xpm);
    multi_button = sprite_build((xpm_map_t) button_multi_xpm);
    button1 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, ORANGE);
    button2 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, BLUE);
    button3 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, GREEN);
    button4 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, YELLOW);
    
}
void delete_sprites(){
    sprite_delete(mouse);
    sprite_delete(button1);
    sprite_delete(button2);
    sprite_delete(button3);
    sprite_delete(button4);
    sprite_delete(initial_screen_background);
    sprite_delete(play_button);
    sprite_delete(quit_button);
    sprite_delete(inst_button);
    sprite_delete(multi_button);
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
