#include "model.h"

extern uint8_t scancode;
SystemState systemstate = ON;
GameState gamestate = START_MENU;
extern vbe_mode_info_t vbe_mode_info;

sprite_t *smile;
sprite_t *button1;
sprite_t *button2;
sprite_t *button3;
sprite_t *button4;

void prepare_sprites(){
    smile = sprite_build((xpm_map_t) smile_xpm);
    button1 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, ORANGE);
    button2 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, BLUE);
    button3 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, GREEN);
    button4 = create_sprite_button(vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2, YELLOW);
}
void delete_sprites(){
    sprite_delete(smile);
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
