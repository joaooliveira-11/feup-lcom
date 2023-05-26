#include "moves.h"

extern mouse_t mouse_packet;

extern struct gamecontext context;

void move_FBup() {
    set_sprite_ypos(&context.sprites[SPRITE_BOY_Idx], context.sprites[SPRITE_BOY_Idx].ypos - 5);
}

void move_FBdown() {
    set_sprite_ypos(&context.sprites[SPRITE_BOY_Idx], context.sprites[SPRITE_BOY_Idx].ypos + 5);
}

void move_FBright() {
    set_sprite_xpos(&context.sprites[SPRITE_BOY_Idx], context.sprites[SPRITE_BOY_Idx].xpos + 5);
}

void move_FBleft() {
    set_sprite_xpos(&context.sprites[SPRITE_BOY_Idx], context.sprites[SPRITE_BOY_Idx].xpos - 5);
}

void move_WGup() {
    set_sprite_ypos(&context.sprites[SPRITE_GIRL_Idx], context.sprites[SPRITE_GIRL_Idx].ypos - 5);
}

void move_WGdown() {
    set_sprite_ypos(&context.sprites[SPRITE_GIRL_Idx],  context.sprites[SPRITE_GIRL_Idx].ypos + 5);
}

void move_WGright() {
     set_sprite_xpos(&context.sprites[SPRITE_GIRL_Idx],  context.sprites[SPRITE_GIRL_Idx].xpos + 5);
}

void move_WGleft() {
    set_sprite_xpos(&context.sprites[SPRITE_GIRL_Idx], context.sprites[SPRITE_GIRL_Idx].xpos - 5);
}



int check_FBmoveUP() {
    return check_colisions(context.sprites[SPRITE_BOY_Idx].xpos, context.sprites[SPRITE_BOY_Idx].ypos - 5,0);
}

int check_FBmoveDOWN() {
    return check_colisions(context.sprites[SPRITE_BOY_Idx].xpos, context.sprites[SPRITE_BOY_Idx].ypos + 5,0);
}

int check_FBmoveRIGHT() {
    return check_colisions(context.sprites[SPRITE_BOY_Idx].xpos + 5, context.sprites[SPRITE_BOY_Idx].ypos,0);
}

int check_FBmoveLEFT() {
    return check_colisions(context.sprites[SPRITE_BOY_Idx].xpos - 5, context.sprites[SPRITE_BOY_Idx].ypos,0);
}

int check_WGmoveUP() {
    return check_colisions(context.sprites[SPRITE_GIRL_Idx].xpos, context.sprites[SPRITE_GIRL_Idx].ypos - 5,1);
}

int check_WGmoveDOWN() {
    return check_colisions(context.sprites[SPRITE_GIRL_Idx].xpos, context.sprites[SPRITE_GIRL_Idx].ypos + 5,1);
}

int check_WGmoveRIGHT() {
     return check_colisions(context.sprites[SPRITE_GIRL_Idx].xpos + 5, context.sprites[SPRITE_GIRL_Idx].ypos,1);
}

int check_WGmoveLEFT() {
    return check_colisions(context.sprites[SPRITE_GIRL_Idx].xpos - 5, context.sprites[SPRITE_GIRL_Idx].ypos,1);
}


int check_colisions(uint16_t targetXPOS, uint16_t targetYPOS, int PlayerType) {
    uint16_t targetWidth = (PlayerType == 0) ? context.sprites[SPRITE_BOY_Idx].width : context.sprites[SPRITE_GIRL_Idx].width;
    uint16_t targetHeight = (PlayerType == 0) ? context.sprites[SPRITE_BOY_Idx].height : context.sprites[SPRITE_GIRL_Idx].height;

    if (targetXPOS <= 25 || targetYPOS <= 15 || targetXPOS + targetWidth >= 775 || targetYPOS + targetHeight >= 580) return 1;


    for (int i = 0; i < context.numWalls; i++) {
        uint16_t wallX = context.walls[i].x;
        uint16_t wallY = context.walls[i].y;

        uint16_t wallWidth = 21;
        uint16_t wallHeight = 20;

        if (targetXPOS + targetWidth >= wallX && targetXPOS <= wallX + wallWidth &&
            targetYPOS + targetHeight >= wallY && targetYPOS <= wallY + wallHeight) {
            return 1;
        }
    }

    return 0;
}

void check_mouse_clicks() {
    if(mouse_packet.lb){
        switch(context.gamestate) {
            case START_MENU:{
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 235 && mouse_packet.ypos <= 332){
                    context.sprites[SPRITE_PLAYbtn_Idx].is_pressed = 1;
                }
                if(mouse_packet.xpos >= 35 && mouse_packet.xpos <= 235 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    context.sprites[SPRITE_INSTbtn_Idx].is_pressed = 1;
                }
                if(mouse_packet.xpos >= 560 && mouse_packet.xpos <= 760 && mouse_packet.ypos >= 365 && mouse_packet.ypos <= 462){
                    context.sprites[SPRITE_QUITbtn_Idx].is_pressed = 1;
                }
                break;
            }
            case INSTRUCTIONS_MENU:
                if(mouse_packet.xpos >= 607 && mouse_packet.xpos <= 777 && mouse_packet.ypos >= 495 && mouse_packet.ypos <= 577){
                    context.sprites[SPRITE_BACKbtn_Idx].is_pressed = 1;
                }  
                break;  

            case GAMEWIN_MENU:
                if(mouse_packet.xpos >= 320 && mouse_packet.xpos <= 490 && mouse_packet.ypos >= 320 && mouse_packet.ypos <= 402){
                    context.sprites[SPRITE_BACKbtn_Idx].is_pressed = 1;
                } 
                 break;
            default:
                break;
        }
        
    }
    else{
        context.sprites[SPRITE_PLAYbtn_Idx].is_pressed = 0;
        context.sprites[SPRITE_QUITbtn_Idx].is_pressed = 0;
        context.sprites[SPRITE_INSTbtn_Idx].is_pressed = 0;
        context.sprites[SPRITE_BACKbtn_Idx].is_pressed = 0;
    }
}

void check_gameWin() {
    if ((context.sprites[SPRITE_BOY_Idx].xpos + context.sprites[SPRITE_BOY_Idx].width >= 663 && context.sprites[SPRITE_BOY_Idx].xpos +  context.sprites[SPRITE_BOY_Idx].width <= 707  &&
            context.sprites[SPRITE_BOY_Idx].ypos + context.sprites[SPRITE_BOY_Idx].height  >= 27 && context.sprites[SPRITE_BOY_Idx].ypos + context.sprites[SPRITE_BOY_Idx].height <= 80) && 
        (context.sprites[SPRITE_GIRL_Idx].xpos + context.sprites[SPRITE_GIRL_Idx].width >= 715 && context.sprites[SPRITE_GIRL_Idx].xpos +  context.sprites[SPRITE_GIRL_Idx].width <= 760  &&
            context.sprites[SPRITE_GIRL_Idx].ypos + context.sprites[SPRITE_GIRL_Idx].height  >= 27 && context.sprites[SPRITE_GIRL_Idx].ypos + context.sprites[SPRITE_GIRL_Idx].height <= 80)){
                context.gamestate = GAMEWIN_MENU;
            } 
}
