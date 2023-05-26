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

    context.walls = malloc(1200 * sizeof(position_t));
    if (context.walls == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int x = 0;
    int y = 0;
    int numPositions = 0; 

    while(ch != EOF){
        ch = fgetc(ptr);
        if(ch == '-'){
             x++;
        }
        if(ch == 'x'){
            context.walls[numPositions].x = x * 20;
            context.walls[numPositions].y = y * 20;
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

void allocate_mouse(){
    sprite_build1(&context.sprites[0], (xpm_map_t) xpms_array[0]);
}

void allocate_buttons(){
    for (int i = 1; i < 6; i++){
        sprite_build1(&context.sprites[i], (xpm_map_t) xpms_array[i]);
    }
}

void allocate_screens(){
    for (int i = 6; i < 10; i++){
        sprite_build1(&context.sprites[i], (xpm_map_t) xpms_array[i]);
    }
}

void allocate_players(){
    for (int i = 10; i < 12; i++){
        sprite_build1(&context.sprites[i], (xpm_map_t) xpms_array[i]);
    }
    set_sprite_xpos(&context.sprites[SPRITE_BOY_Idx], 25);
    set_sprite_ypos(&context.sprites[SPRITE_BOY_Idx], 515);
    set_sprite_xpos(&context.sprites[SPRITE_GIRL_Idx], 25);
    set_sprite_ypos(&context.sprites[SPRITE_GIRL_Idx], 515);
}

void allocate_game_elements(){
    for (int i = 12; i < 14; i++){
        sprite_build1(&context.sprites[i], (xpm_map_t) xpms_array[i]);
    }
    if(read_map() != 0) printf("error while reading game map\n");
}

void delete_screens(){
    /*
    sprite_delete(context.initial_screen_background);
    sprite_delete(context.instructions_screen);
    sprite_delete(context.game_screen);
    sprite_delete(context.wall);
    sprite_delete(context.doors);
    sprite_delete(context.win_screen);
    */
}

void delete_game_elements(){
    //sprite_delete(context.mouse);
    free(context.walls);
}

void delete_players(){
    /*
    sprite_delete(context.boy);
    sprite_delete(context.girl);
    */
}

void delete_buttons(){
    /*
    sprite_delete(context.play_button);
    sprite_delete(context.quit_button);
    sprite_delete(context.inst_button);
    sprite_delete(context.multi_button);
    sprite_delete(context.back_button);
    */
}
