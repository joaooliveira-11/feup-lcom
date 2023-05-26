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
        case arrowup:{
            if(context.gamestate == PLAYING){
               if(check_FBmoveUP() == 0){
                    move_FBup();
                    check_gameWin();
               }
            }
            break;
        }
        case arrowdown:{
            if(context.gamestate == PLAYING){
                if(check_FBmoveDOWN() == 0){
                    move_FBdown();
                    check_gameWin();
               }
            }
            break;
        }
        case arrowright:{
            if(context.gamestate == PLAYING){
                if(check_FBmoveRIGHT() == 0){
                    move_FBright();
                    check_gameWin();
               }
            }
            break;
        }
        case arrowleft:{
            if(context.gamestate == PLAYING){
                if(check_FBmoveLEFT() == 0){
                    move_FBleft();
                    check_gameWin();
               }
            }
            break;
        }

        case W:{
            if(context.gamestate == PLAYING){
                if(check_WGmoveUP() == 0){
                    move_WGup();
                    check_gameWin();
               }
            }
            break;
        }
        case S:{
            if(context.gamestate == PLAYING){
                if(check_WGmoveDOWN() == 0){
                    move_WGdown();
                    check_gameWin();
               }
            }
            break;
        }
        case D:{
            if(context.gamestate == PLAYING){
                if(check_WGmoveRIGHT() == 0){
                    move_WGright();
                    check_gameWin();
               }
            }
            break;
        }
        case A:{
            if(context.gamestate == PLAYING){
                if(check_WGmoveLEFT() == 0){
                    move_WGleft();
                    check_gameWin();
               }
            }
            break;
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
