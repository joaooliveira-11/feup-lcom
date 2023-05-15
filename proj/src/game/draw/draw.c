#include "draw.h"

uint8_t *first_frame_buffer;
uint8_t *second_frame_buffer;
uint32_t frame_buffer_size;

extern vbe_mode_info_t vbe_mode_info;
extern Status gamestatus;
extern GameState gamestate;
extern mouse_t mouse_packet;
extern sprite_t *mouse;
extern sprite_t *play_button;
extern sprite_t *quit_button;
extern sprite_t *inst_button;
extern sprite_t *multi_button;
extern sprite_t *initial_screen_background;
extern sprite_t *instructions_screen;
extern sprite_t *back_button;
extern sprite_t *game_screen;
extern sprite_t *boy;
extern sprite_t *girl;
extern sprite_t *boy_left;
extern sprite_t *boy_right;
extern sprite_t *girl_left;
extern sprite_t *girl_right;
extern sprite_t *wall;

extern watergirl_t watergirl;
extern fireboy_t fireboy;


int draw_map(){
    char buf[1024];
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("Current working directory: %s\n", buf);
    } else {
        perror("getcwd() error");
        return 1;
    }

    char *filename = "/home/lcom/labs/g1/proj/src/game/draw/map.txt";

    FILE *ptr;
    char ch = '\0';
    ptr = fopen(filename, "r");


    
    if(ptr == NULL){
        printf("file cant open");
        return 1;
    }
    int x = 0;
    int y = 0;


    while(ch != EOF){
        ch = fgetc(ptr);
        if(ch == 'x'){
             x++;
        }
        if(ch == '-'){
            draw_staticSprite_xpm(wall, x*20, y*20);
            x++;
        }if(ch == '|'){
                y++;
                x = 0;
            }
        }

    fclose(ptr);

    return 0;
}

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
        current_color = sprite->colors_array[x + y*sprite->width];
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
        current_color = sprite->colors_array[x + y*sprite->width];
        if (current_color == TRANSPARENT) continue;
        if (color_pixel(sprite_xpos + x, sprite_ypos + y, current_color, second_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}

void draw_frame() {
    if(quit_button->is_pressed){
        gamestatus = OFF;
        return;
    }
    if(play_button->is_pressed) gamestate = PLAYING;
    if(inst_button->is_pressed) gamestate = INSTRUCTIONS_MENU;
    if(back_button->is_pressed) gamestate = START_MENU;

    switch (gamestate) {
        case START_MENU:
            draw_initial_menu_screen();
            break;
        case PLAYING:
            draw_game_screen();
            break;
        case INSTRUCTIONS_MENU:
            draw_instructions_menu_screen();
            break;
    }
    draw_newMouse_pos();
}


void draw_initial_menu_screen() {
    draw_staticSprite_xpm(initial_screen_background, 0,0);
    draw_staticSprite_xpm(play_button,35,235);
    draw_staticSprite_xpm(quit_button,560,365);
    draw_staticSprite_xpm(inst_button,35,365);
    draw_staticSprite_xpm(multi_button,560,235);
}

void draw_instructions_menu_screen() {
    draw_staticSprite_xpm(instructions_screen,0,0);
    draw_staticSprite_xpm(back_button, 607,495);
}


void draw_game_screen(){
    draw_staticSprite_xpm(game_screen,0,0);
    draw_map();
    switch(fireboy.type){
        case 0: 
            draw_movingSprite_xpm(boy);
            break;
        case 1:
            draw_movingSprite_xpm(boy_left);
            break;
        case 2:
            draw_movingSprite_xpm(boy_right);
            break;
        default:
            break;
    }
    switch(watergirl.type){
        case 0: 
            draw_movingSprite_xpm(girl);
            break;
        case 1:
            draw_movingSprite_xpm(girl_left);
            break;
        case 2:
            draw_movingSprite_xpm(girl_right);
            break;
        default:
            break;
    }
}

void draw_newMouse_pos(){
    set_sprite_xpos(mouse, mouse_packet.xpos);
    set_sprite_ypos(mouse, mouse_packet.ypos);
    draw_movingSprite_xpm(mouse);
}

