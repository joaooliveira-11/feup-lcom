#include "interrupts.h"

extern uint8_t scancode;
extern uint8_t mouse_byte_index; 

extern vbe_mode_info_t vbe_mode_info;
extern mouse_t mouse_packet;
extern struct gamecontext context;


void handle_timer_interrupt(){
    update_buffers();
}

void move_action(GameState state, int (check_move)(), void (move_player)() ){
    if(context.gamestate == state){
        if(check_move() == 0){
            move_player();
            check_gameWin();
        }
    }
}

void handle_keyboard_interrupt(){
    (kbc_ih)();
    switch (scancode) {
        case QUIT:
            context.gamestatus = OFF;
            break;
        case arrowup:{
            move_action(PLAYING, check_FBmoveUP, move_FBup);
            break;
        }
        case arrowdown:{
            move_action(PLAYING, check_FBmoveDOWN, move_FBdown);
            break;
        }
        case arrowright:{
            move_action(PLAYING, check_FBmoveRIGHT,move_FBright);
            break;
        }
        case arrowleft:{
            move_action(PLAYING, check_FBmoveLEFT, move_FBleft);
            break;
        }
        case W:{
            move_action(PLAYING, check_WGmoveUP, move_WGup);
            break;
        }
        case S:{
            move_action(PLAYING, check_WGmoveDOWN, move_WGdown);
            break;
        }
        case D:{
            move_action(PLAYING, check_WGmoveRIGHT, move_WGright);
            break;
        }
        case A:{
            move_action(PLAYING, check_WGmoveLEFT, move_WGleft);
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
