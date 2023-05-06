#include "elements.h"

watergirl_t watergirl;
fireboy_t fireboy;

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


void allocate_screens(){
    initial_screen_background = sprite_build((xpm_map_t) background_final_xpm);
    instructions_screen = sprite_build((xpm_map_t) instructions_xpm);
    game_screen = sprite_build((xpm_map_t) game_backgroung_xpm);
}

void allocate_game_elements(){
    mouse = sprite_build((xpm_map_t) mouse_xpm);
}

void allocate_players(){
    boy = sprite_build((xpm_map_t) fireboy_xpm);
    girl = sprite_build((xpm_map_t) watergirl_xpm);

    boy_left = sprite_build((xpm_map_t) running_left_boy_xpm);
    boy_right = sprite_build((xpm_map_t) running_right_boy_xpm);
    girl_left = sprite_build((xpm_map_t) running_left_girl_xpm);
    girl_right = sprite_build((xpm_map_t) running_right_girl_xpm); 

    fireboy.xpos = 35;
    fireboy.ypos = 235;
    fireboy.type = 0;

    watergirl.xpos = 35;
    watergirl.ypos = 365;
    watergirl.type = 0;

    set_sprite_xpos(boy, fireboy.xpos);
    set_sprite_ypos(boy, fireboy.ypos);
    set_sprite_xpos(girl, watergirl.xpos);
    set_sprite_ypos(girl, watergirl.ypos);

}

void allocate_buttons(){
    play_button = sprite_build((xpm_map_t) button_play_xpm);
    quit_button = sprite_build((xpm_map_t) button_quit_xpm);
    inst_button = sprite_build((xpm_map_t) button_inst_xpm);
    multi_button = sprite_build((xpm_map_t) button_multi_xpm);
    back_button = sprite_build((xpm_map_t) button_back_xpm);

}

void delete_screens(){
    sprite_delete(initial_screen_background);
    sprite_delete(instructions_screen);
    sprite_delete(game_screen);
}

void delete_game_elements(){
    sprite_delete(mouse);
}

void delete_players(){
    sprite_delete(boy);
    sprite_delete(boy_left);
    sprite_delete(boy_right);
    sprite_delete(girl_left);
    sprite_delete(girl_right);
    sprite_delete(girl);
}

void delete_buttons(){
    sprite_delete(play_button);
    sprite_delete(quit_button);
    sprite_delete(inst_button);
    sprite_delete(multi_button);
    sprite_delete(back_button);
}
