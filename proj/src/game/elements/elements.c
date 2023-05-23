#include "elements.h"
#include "../context.h"

extern struct gamecontext context;

int read_map(){
    char buf[1024];
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("Current working directory: %s\n", buf);
    } else {
        perror("getcwd() error");
        return 1;
    }

    FILE *ptr;
    char ch = '\0';
    ptr = fopen("/home/lcom/labs/g1/proj/src/game/draw/map.txt", "r");

    if(ptr == NULL){
        printf("file cant open");
        return 1;
    }

    context.positions = malloc(1200 * sizeof(position_t));
    if (context.positions == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int x = 0;
    int y = 0;
    int numPositions = 0; 

    while(ch != EOF){
        ch = fgetc(ptr);
        if(ch == 'x'){
             x++;
        }
        if(ch == '-'){
            context.positions[numPositions].x = x * 20;
            context.positions[numPositions].y = y * 20;
            numPositions++;
            x++;
        }if(ch == '|'){
                y++;
                x = 0;
            }
    }

    context.numWalls = numPositions;
    fclose(ptr);

    return 0;
}

void allocate_screens(){
    context.initial_screen_background = sprite_build((xpm_map_t) background_final_xpm);
    context.instructions_screen = sprite_build((xpm_map_t) instructions_xpm);
    context.game_screen = sprite_build((xpm_map_t) game_backgroung_xpm);
    context.wall = sprite_build((xpm_map_t) wall_xpm);
}

void allocate_game_elements(){
    context.mouse = sprite_build((xpm_map_t) mouse_xpm);
    if(read_map() != 0) printf("error while reading game map\n");
}

void allocate_players(){
    context.boy = sprite_build((xpm_map_t) fireboy_xpm);
    context.girl = sprite_build((xpm_map_t) watergirl_xpm);

    context.boy_left = sprite_build((xpm_map_t) running_left_boy_xpm);
    context.boy_right = sprite_build((xpm_map_t) running_right_boy_xpm);
    context.girl_left = sprite_build((xpm_map_t) running_left_girl_xpm);
    context.girl_right = sprite_build((xpm_map_t) running_right_girl_xpm); 

    context.fireboy.xpos = 35;
    context.fireboy.ypos = 235;
    context.fireboy.type = 0;

    context.watergirl.xpos = 35;
    context.watergirl.ypos = 365;
    context.watergirl.type = 0;

    set_sprite_xpos(context.boy, context.fireboy.xpos);
    set_sprite_ypos(context.boy, context.fireboy.ypos);
    set_sprite_xpos(context.girl, context.watergirl.xpos);
    set_sprite_ypos(context.girl, context.watergirl.ypos);

}

void allocate_buttons(){
    context.play_button = sprite_build((xpm_map_t) button_play_xpm);
    context.quit_button = sprite_build((xpm_map_t) button_quit_xpm);
    context.inst_button = sprite_build((xpm_map_t) button_inst_xpm);
    context.multi_button = sprite_build((xpm_map_t) button_multi_xpm);
    context.back_button = sprite_build((xpm_map_t) button_back_xpm);

}

void delete_screens(){
    sprite_delete(context.initial_screen_background);
    sprite_delete(context.instructions_screen);
    sprite_delete(context.game_screen);
    sprite_delete(context.wall);
}

void delete_game_elements(){
    sprite_delete(context.mouse);
    free(context.positions);
}

void delete_players(){
    sprite_delete(context.boy);
    sprite_delete(context.boy_left);
    sprite_delete(context.boy_right);
    sprite_delete(context.girl_left);
    sprite_delete(context.girl_right);
    sprite_delete(context.girl);
}

void delete_buttons(){
    sprite_delete(context.play_button);
    sprite_delete(context.quit_button);
    sprite_delete(context.inst_button);
    sprite_delete(context.multi_button);
    sprite_delete(context.back_button);
}
