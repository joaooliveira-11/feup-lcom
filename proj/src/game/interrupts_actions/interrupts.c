#include "interrupts.h"

extern uint8_t scancode;
extern uint8_t mouse_byte_index; 
extern Status gamestatus;
extern GameState gamestate;
extern vbe_mode_info_t vbe_mode_info;
extern mouse_t mouse_packet;

extern sprite_t *boy;
extern sprite_t *girl;
extern sprite_t *boy_left;
extern sprite_t *boy_right;
extern sprite_t *girl_left;
extern sprite_t *girl_right;
extern watergirl_t watergirl;
extern fireboy_t fireboy;

void handle_timer_interrupt(){
    update_buffers();
}

void handle_keyboard_interrupt(){
    (kbc_ih)();
    switch (scancode) {
        case QUIT:
            gamestatus = OFF;
            break;
        case GAME_SCREEN:
            gamestate = PLAYING;
            break;
        case arrowup:{
            if(gamestate == PLAYING){
                if(check_arena_border(fireboy.xpos, fireboy.xpos + boy->width, fireboy.ypos -5, fireboy.ypos -5) == 0){
                    fireboy.ypos -= 5;
                    fireboy.type = 0;
                    set_sprite_xpos(boy, fireboy.xpos);
                    set_sprite_ypos(boy, fireboy.ypos);
                }
                break;
            }
        }
        case arrowdown:{
            if(gamestate == PLAYING){
                if(check_arena_border(fireboy.xpos, fireboy.xpos + boy->width, fireboy.ypos +5, fireboy.ypos +5 + boy->height) == 0){
                    fireboy.ypos += 5;
                    fireboy.type = 0;
                    set_sprite_xpos(boy, fireboy.xpos);
                    set_sprite_ypos(boy, fireboy.ypos);
                }
                break;
            }
        }
        case arrowright:{
            if(gamestate == PLAYING){
                if(check_arena_border(fireboy.xpos +5 , fireboy.xpos + 5 + boy_right->width, fireboy.ypos, fireboy.ypos) == 0){
                    fireboy.xpos += 5;
                    if(fireboy.type == 0) fireboy.ypos += 10;
                    fireboy.type = 2;
                    set_sprite_xpos(boy_right, fireboy.xpos);
                    set_sprite_ypos(boy_right, fireboy.ypos);
                }
                break;
            }
        }
        case arrowleft:{
            if(gamestate == PLAYING){
                if(check_arena_border(fireboy.xpos -5 , fireboy.xpos -5, fireboy.ypos, fireboy.ypos) == 0){
                    if(fireboy.type == 0) fireboy.ypos += 10;
                    fireboy.type = 1;
                    fireboy.xpos -= 5;
                    set_sprite_xpos(boy_left, fireboy.xpos);
                    set_sprite_ypos(boy_left, fireboy.ypos);
                }
                break;
            }
        }

        case W:{
            if(gamestate == PLAYING){
                if(check_arena_border(watergirl.xpos, watergirl.xpos + girl->width, watergirl.ypos -5, watergirl.ypos -5) == 0){
                    watergirl.ypos -= 5;
                    watergirl.type = 0;
                    set_sprite_xpos(girl, watergirl.xpos);
                    set_sprite_ypos(girl, watergirl.ypos);
                }
                break;
            }
        }
        case S:{
            if(gamestate == PLAYING){
                if(check_arena_border(watergirl.xpos, watergirl.xpos + girl->width, watergirl.ypos +5, watergirl.ypos +5 + girl->height) == 0){
                    watergirl.ypos += 5;
                    watergirl.type = 0;
                    set_sprite_xpos(girl, watergirl.xpos);
                    set_sprite_ypos(girl, watergirl.ypos);
                }
                break;
            }
        }
        case D:{
            if(gamestate == PLAYING){
                if(check_arena_border(watergirl.xpos +5 , watergirl.xpos + 5 + girl_right->width, watergirl.ypos, watergirl.ypos) == 0){
                    watergirl.xpos += 5;
                    if(watergirl.type == 0) watergirl.ypos += 6;
                    watergirl.type = 2;
                    set_sprite_xpos(girl_right, watergirl.xpos);
                    set_sprite_ypos(girl_right, watergirl.ypos);
                }
                break;
            }
        }
        case A:{
            if(gamestate == PLAYING){
                if(check_arena_border(watergirl.xpos -5 , watergirl.xpos -5, watergirl.ypos, watergirl.ypos) == 0){
                    if(watergirl.type == 0) watergirl.ypos += 6;
                    watergirl.type = 1;
                    watergirl.xpos -= 5;
                    set_sprite_xpos(girl_left, watergirl.xpos);
                    set_sprite_ypos(girl_left, watergirl.ypos);
                }
                break;
            }
        }

        default:
            break;
    }
    draw_frame();
}


void handle_mouse_interrupt(){
    mouse_ih();
    mouse_sync_bytes();
    if(mouse_byte_index == 3){
        mouse_bytes_to_packet();
        draw_frame();
        check_mouse_clicks();
        mouse_byte_index = 0;
    }
}

