#include "moves.h"

extern mouse_t mouse_packet;

extern struct gamecontext context;

int check_arena_border(uint16_t sprite_initialX, uint16_t sprite_finalX, uint16_t sprite_initialY, uint16_t sprite_finalY){
    if(sprite_initialY <= 32 || sprite_finalY <= 32 || sprite_initialY >= 570 || sprite_finalY >= 570) return 1;
    if(sprite_initialX <= 25 || sprite_finalX <= 25 || sprite_initialX >= 775 || sprite_finalX >= 775) return 1;
    return 0;
}

void check_mouse_clicks(){
    if(mouse_packet.lb){
        switch(context.gamestate) {
            case START_MENU:{
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 235 && mouse_packet.ypos <= 332){
                    context.play_button->is_pressed = 1;
                }
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    context.inst_button->is_pressed = 1;
                }
                if(mouse_packet.xpos >= 560 && mouse_packet.xpos <= 760 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    context.quit_button->is_pressed = 1;
                }
                break;
            }
            case INSTRUCTIONS_MENU:
                if(mouse_packet.xpos >= 607 && mouse_packet.xpos <= 777 && mouse_packet.ypos >= 495 && mouse_packet.ypos <= 577){
                  context.back_button->is_pressed = 1;
                }  
                break;   
            default:
                break;
        }
        
    }
    else{
        context.play_button->is_pressed = 0;
        context.quit_button->is_pressed = 0;
        context.inst_button->is_pressed = 0;
        context.back_button->is_pressed = 0;
    }
}

