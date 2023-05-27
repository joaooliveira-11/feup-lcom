#include "draw.h"

uint8_t *first_frame_buffer;
uint8_t *second_frame_buffer;
uint32_t frame_buffer_size;

extern vbe_mode_info_t vbe_mode_info;
extern mouse_t mouse_packet;
extern struct gamecontext context;


int allocate_double_buffer(uint16_t mode) {
    if (frame_buffer_build(mode, &first_frame_buffer)) return 1;
    frame_buffer_size = vbe_mode_info.XResolution * vbe_mode_info.YResolution * ((vbe_mode_info.BitsPerPixel + 7) / 8);
    second_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
    return 0;
}

void update_buffers() {
    memcpy(first_frame_buffer, second_frame_buffer, frame_buffer_size);
}


int draw_movingSprite_xpm(sprite_t *sprite) { 
    uint16_t sprite_xpos = get_sprite_xpos(sprite);
    uint16_t sprite_ypos = get_sprite_ypos(sprite);
    uint32_t current_color;
    for (int y = 0 ; y < sprite->height ; y++) {
      for (int x = 0 ; x < sprite->width ; x++) {
        current_color = sprite->xpm[x + y*sprite->width];
        if (current_color == TRANSPARENT) continue;
        if (color_pixel(sprite_xpos + x, sprite_ypos + y, current_color, second_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}

int draw_staticSprite_xpm(sprite_t *sprite, uint16_t x, uint16_t y) { 
    uint16_t sprite_xpos = x;
    uint16_t sprite_ypos = y;
    uint32_t current_color;
    for (int y = 0 ; y < sprite->height ; y++) {
      for (int x = 0 ; x < sprite->width ; x++) {
        current_color = sprite->xpm[x + y*sprite->width];
        if (current_color == TRANSPARENT) continue;
        if (color_pixel(sprite_xpos + x, sprite_ypos + y, current_color, second_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}

void draw_map(){
    for (int i = 0; i < context.numWalls; i++) {
        uint16_t xPos = context.walls[i].x;
        uint16_t yPos = context.walls[i].y;
        draw_staticSprite_xpm(&context.sprites[SPRITE_WALL_Idx], xPos, yPos);
    }

    for(int i = 0; i < 3; i++){
        if(context.barriers[i].is_open && (context.levers[i].is_pressed || context.levers_match[i].is_pressed)){
            if(context.levers[i].is_pressed){
                draw_staticSprite_xpm(&context.sprites[SPRITE_LEVERright_Idx], context.levers[i].x, context.levers[i].y);
                draw_staticSprite_xpm(&context.sprites[SPRITE_LEVERleft_Idx], context.levers_match[i].x, context.levers_match[i].y);
            }
            else if(context.levers_match[i].is_pressed){
                draw_staticSprite_xpm(&context.sprites[SPRITE_LEVERleft_Idx], context.levers[i].x, context.levers[i].y);
                draw_staticSprite_xpm(&context.sprites[SPRITE_LEVERright_Idx], context.levers_match[i].x, context.levers_match[i].y);
            }
        }
        else{
            draw_staticSprite_xpm(&context.sprites[SPRITE_BARRIER_Idx], context.barriers[i].x, context.barriers[i].y);
            draw_staticSprite_xpm(&context.sprites[SPRITE_LEVERleft_Idx], context.levers[i].x, context.levers[i].y);
            draw_staticSprite_xpm(&context.sprites[SPRITE_LEVERleft_Idx], context.levers_match[i].x, context.levers_match[i].y);
        }
    }

    for(int i = 0; i < context.numTraps; i++){
        uint16_t xPos = context.traps[i].x;
        uint16_t yPos = context.traps[i].y;
        if(context.traps[i].type == 1){
            draw_staticSprite_xpm(&context.sprites[SPRITE_FIRE_Idx], xPos, yPos);
        }if(context.traps[i].type == 0){
            draw_staticSprite_xpm(&context.sprites[SPRITE_ICE_Idx], xPos, yPos);
        }
    }
}

void draw_frame() {
    if(context.sprites[SPRITE_QUITbtn_Idx].is_pressed){
        context.gamestatus = OFF;
        return;
    }
    if(context.sprites[SPRITE_PLAYbtn_Idx].is_pressed) context.gamestate = PLAYING;
    if(context.sprites[SPRITE_INSTbtn_Idx].is_pressed) context.gamestate = INSTRUCTIONS_MENU;
    if(context.sprites[SPRITE_BACKbtn_Idx].is_pressed) context.gamestate = START_MENU;

    switch (context.gamestate) {
        case START_MENU:
            draw_initial_menu_screen();
            break;
        case PLAYING:
            draw_game_screen();
            break;
        case INSTRUCTIONS_MENU:
            draw_instructions_menu_screen();
            break;
        case GAMEWIN_MENU:
            draw_win_screen();
            break;
        case GAMEOVER_MENU:
            draw_lose_screen();
            break;     
    }
    draw_newMouse_pos();
}


void draw_initial_menu_screen() {
    draw_staticSprite_xpm(&context.sprites[SPRITE_INITscreen_Idx], 0,0);
    draw_staticSprite_xpm(&context.sprites[SPRITE_PLAYbtn_Idx],35,235);
    draw_staticSprite_xpm(&context.sprites[SPRITE_QUITbtn_Idx],560,365);
    draw_staticSprite_xpm(&context.sprites[SPRITE_INSTbtn_Idx],35,365);
    draw_staticSprite_xpm(&context.sprites[SPRITE_MULTIbtn_Idx],560,235);

    set_sprite_xpos(&context.sprites[SPRITE_PLAYbtn_Idx], 35);
    set_sprite_ypos(&context.sprites[SPRITE_PLAYbtn_Idx], 235);

    set_sprite_xpos(&context.sprites[SPRITE_QUITbtn_Idx], 560);
    set_sprite_ypos(&context.sprites[SPRITE_QUITbtn_Idx], 365);

    set_sprite_xpos(&context.sprites[SPRITE_INSTbtn_Idx], 35);
    set_sprite_ypos(&context.sprites[SPRITE_INSTbtn_Idx], 365);

    set_sprite_xpos(&context.sprites[SPRITE_MULTIbtn_Idx], 560);
    set_sprite_ypos(&context.sprites[SPRITE_MULTIbtn_Idx], 235);

}

void draw_instructions_menu_screen() {
    draw_staticSprite_xpm(&context.sprites[SPRITE_INSTscreen_Idx],0,0);
    draw_staticSprite_xpm(&context.sprites[SPRITE_BACKbtn_Idx], 607, 495);

    set_sprite_xpos(&context.sprites[SPRITE_BACKbtn_Idx], 607);
    set_sprite_ypos(&context.sprites[SPRITE_BACKbtn_Idx], 495);
}

void draw_win_screen() {
    draw_staticSprite_xpm(&context.sprites[SPRITE_WINscree_Idx],0,0);
    draw_staticSprite_xpm(&context.sprites[SPRITE_BACKbtn_Idx], 320, 320);
}

void draw_game_screen(){
    draw_staticSprite_xpm(&context.sprites[SPRITE_GAMEscreen_Idx],0,0);
    draw_map();
    draw_staticSprite_xpm(&context.sprites[SPRITE_DOOR_Idx], 663, 27);
    draw_movingSprite_xpm(&context.sprites[SPRITE_BOY_Idx]);
    draw_movingSprite_xpm(&context.sprites[SPRITE_GIRL_Idx]);
}

void draw_newMouse_pos(){
    set_sprite_xpos(&context.sprites[SPRITE_MOUSE_Idx], mouse_packet.xpos);
    set_sprite_ypos(&context.sprites[SPRITE_MOUSE_Idx], mouse_packet.ypos);
    draw_movingSprite_xpm(&context.sprites[SPRITE_MOUSE_Idx]);
}

void draw_lose_screen() {
    draw_staticSprite_xpm(&context.sprites[SPRITE_LOSEscree_Idx],0,0);
    draw_staticSprite_xpm(&context.sprites[SPRITE_BACKbtn_Idx], 320, 320);
}
