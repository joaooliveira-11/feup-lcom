#include "moves.h"

extern GameState gamestate;
extern mouse_t mouse_packet;

extern sprite_t *play_button;
extern sprite_t *quit_button;
extern sprite_t *inst_button;
extern sprite_t *multi_button;
extern sprite_t *back_button;

int check_arena_border(uint16_t sprite_initialX, uint16_t sprite_finalX, uint16_t sprite_initialY, uint16_t sprite_finalY){
    if(sprite_initialY <= 32 || sprite_finalY <= 32 || sprite_initialY >= 570 || sprite_finalY >= 570) return 1;
    if(sprite_initialX <= 25 || sprite_finalX <= 25 || sprite_initialX >= 775 || sprite_finalX >= 775) return 1;
    return 0;
}

void check_mouse_clicks(){
    if(mouse_packet.lb){
        switch(gamestate) {
            case START_MENU:{
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 235 && mouse_packet.ypos <= 332){
                    play_button->is_pressed = 1;
                }
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    inst_button->is_pressed = 1;
                }
                if(mouse_packet.xpos >= 560 && mouse_packet.xpos <= 760 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    quit_button->is_pressed = 1;
                }
                break;
            }
            case INSTRUCTIONS_MENU:
                if(mouse_packet.xpos >= 607 && mouse_packet.xpos <= 777 && mouse_packet.ypos >= 495 && mouse_packet.ypos <= 577){
                  back_button->is_pressed = 1;
                }  
                break;   
            default:
                break;
        }
        
    }
    else{
        play_button->is_pressed = 0;
        quit_button->is_pressed = 0;
        inst_button->is_pressed = 0;
        back_button->is_pressed = 0;
    }
}

