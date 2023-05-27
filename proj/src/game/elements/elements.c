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
    context.levers = malloc(10 * sizeof(lever_t));
    context.levers_match = malloc(10 * sizeof(lever_t));
    context.barriers = malloc(10 * sizeof(barrier_t));
    context.traps = malloc(10 * sizeof(barrier_t));

    if (context.walls == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (context.levers== NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (context.levers_match == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (context.barriers == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (context.traps == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int x = 0;
    int y = 0;
    int numPositions = 0;
    int numTraps = 0; 

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
        if(ch == 'A'){
            context.barriers[0].x = x * 20;
            context.barriers[0].y = y * 20;
            context.barriers[0].is_open = 0;
            x += 2;
        }
        if(ch == 'B'){
            context.barriers[1].x = x * 20;
            context.barriers[1].y = y * 20;
            context.barriers[1].is_open = 0;
            x += 2;
        }
        if(ch == 'C'){
            context.barriers[2].x = x * 20;
            context.barriers[2].y = y * 20;
            context.barriers[2].is_open = 0;
            x += 2;
        }
        if(ch == '1'){
            context.levers[0].x = x * 20;
            context.levers[0].y = y * 20;
            context.levers[0].is_pressed = 0;
            x++;
        }
        if(ch == '2'){
            context.levers_match[0].x = x * 20;
            context.levers_match[0].y = y * 20;
            context.levers_match[0].is_pressed = 0;
            x++;
        }
        if(ch == '3'){
            context.levers[1].x = x * 20;
            context.levers[1].y = y * 20;
            context.levers[1].is_pressed = 0;
            x++;
        }
        if(ch == '4'){
            context.levers_match[1].x = x * 20;
            context.levers_match[1].y = y * 20;
            context.levers_match[1].is_pressed = 0;
            x++;
        }
        if(ch == '5'){
            context.levers[2].x = x * 20;
            context.levers[2].y = y * 20;
            context.levers[2].is_pressed = 0;
            x++;
        }
        if(ch == '6'){
            context.levers_match[2].x = x * 20;
            context.levers_match[2].y = y * 20;
            context.levers_match[2].is_pressed = 0;
            x++;
        }
        if(ch == 'f'){
            context.traps[numTraps].x = x * 20;
            context.traps[numTraps].y = y * 20;
            context.traps[numTraps].type = 1;
            x+=2;
            numTraps++;
        }
        if(ch == 'i'){
            context.traps[numTraps].x = x * 20;
            context.traps[numTraps].y = y * 20;
            context.traps[numTraps].type = 0;
            x+=2;
            numTraps++;
        }
    }

    context.numWalls = numPositions;
    context.numTraps = numTraps;
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
    for (int i = 6; i < 11; i++){
        sprite_build1(&context.sprites[i], (xpm_map_t) xpms_array[i]);
    }
}

void allocate_players(){
    for (int i = 11; i < 13; i++){
        sprite_build1(&context.sprites[i], (xpm_map_t) xpms_array[i]);
    }
    set_sprite_xpos(&context.sprites[SPRITE_BOY_Idx], 25);
    set_sprite_ypos(&context.sprites[SPRITE_BOY_Idx], 515);
    set_sprite_xpos(&context.sprites[SPRITE_GIRL_Idx], 25);
    set_sprite_ypos(&context.sprites[SPRITE_GIRL_Idx], 515);
}

void allocate_game_elements(){
    for (int i = 13; i < 20; i++){
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
    free(context.traps);
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
