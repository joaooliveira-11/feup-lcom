#include "interrupts.h"

extern uint8_t scancode;
extern uint8_t mouse_byte_index; 

extern vbe_mode_info_t vbe_mode_info;
extern mouse_t mouse_packet;
extern struct gamecontext context;


void handle_timer_interrupt(){
    update_buffers();
}

void handle_keyboard_interrupt(){
    (kbc_ih)();
    switch (scancode) {
        case QUIT:
            context.gamestatus = OFF;
            break;
        case GAME_SCREEN:
            context.gamestate = PLAYING;
            break;
        case arrowup:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.fireboy.xpos, context.fireboy.xpos + context.boy->width, context.fireboy.ypos -5, context.fireboy.ypos -5) == 0){
                    context.fireboy.ypos -= 5;
                    context.fireboy.type = 0;
                    set_sprite_xpos(context.boy, context.fireboy.xpos);
                    set_sprite_ypos(context.boy, context.fireboy.ypos);
                }
                break;
            }
        }
        case arrowdown:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.fireboy.xpos, context.fireboy.xpos + context.boy->width, context.fireboy.ypos +5, context.fireboy.ypos +5 + context.boy->height) == 0){
                    context.fireboy.ypos += 5;
                    context.fireboy.type = 0;
                    set_sprite_xpos(context.boy, context.fireboy.xpos);
                    set_sprite_ypos(context.boy, context.fireboy.ypos);
                }
                break;
            }
        }
        case arrowright:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.fireboy.xpos +5 , context.fireboy.xpos + 5 + context.boy_right->width, context.fireboy.ypos, context.fireboy.ypos) == 0){
                    context.fireboy.xpos += 5;
                    if(context.fireboy.type == 0) context.fireboy.ypos += 10;
                    context.fireboy.type = 2;
                    set_sprite_xpos(context.boy_right, context.fireboy.xpos);
                    set_sprite_ypos(context.boy_right, context.fireboy.ypos);
                }
                break;
            }
        }
        case arrowleft:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.fireboy.xpos -5 , context.fireboy.xpos -5, context.fireboy.ypos, context.fireboy.ypos) == 0){
                    if(context.fireboy.type == 0) context.fireboy.ypos += 10;
                    context.fireboy.type = 1;
                    context.fireboy.xpos -= 5;
                    set_sprite_xpos(context.boy_left, context.fireboy.xpos);
                    set_sprite_ypos(context.boy_left, context.fireboy.ypos);
                }
                break;
            }
        }

        case W:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.watergirl.xpos, context.watergirl.xpos + context.girl->width, context.watergirl.ypos -5, context.watergirl.ypos -5) == 0){
                    context.watergirl.ypos -= 5;
                    context.watergirl.type = 0;
                    set_sprite_xpos(context.girl, context.watergirl.xpos);
                    set_sprite_ypos(context.girl, context.watergirl.ypos);
                }
                break;
            }
        }
        case S:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.watergirl.xpos, context.watergirl.xpos + context.girl->width, context.watergirl.ypos +5, context.watergirl.ypos +5 + context.girl->height) == 0){
                    context.watergirl.ypos += 5;
                    context.watergirl.type = 0;
                    set_sprite_xpos(context.girl, context.watergirl.xpos);
                    set_sprite_ypos(context.girl, context.watergirl.ypos);
                }
                break;
            }
        }
        case D:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.watergirl.xpos +5 , context.watergirl.xpos + 5 + context.girl_right->width, context.watergirl.ypos, context.watergirl.ypos) == 0){
                    context.watergirl.xpos += 5;
                    if(context.watergirl.type == 0) context.watergirl.ypos += 6;
                    context.watergirl.type = 2;
                    set_sprite_xpos(context.girl_right, context.watergirl.xpos);
                    set_sprite_ypos(context.girl_right, context.watergirl.ypos);
                }
                break;
            }
        }
        case A:{
            if(context.gamestate == PLAYING){
                if(check_arena_border(context.watergirl.xpos -5 , context.watergirl.xpos -5, context.watergirl.ypos, context.watergirl.ypos) == 0){
                    if(context.watergirl.type == 0) context.watergirl.ypos += 6;
                    context.watergirl.type = 1;
                    context.watergirl.xpos -= 5;
                    set_sprite_xpos(context.girl_left, context.watergirl.xpos);
                    set_sprite_ypos(context.girl_left, context.watergirl.ypos);
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

