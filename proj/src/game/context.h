#ifndef CONTEXT_H_
#define CONTEXT_H_

typedef enum {
    ON,
    OFF,
} Status;

typedef enum {
    START_MENU,
    GAMEWIN_MENU,
    //GAMEOVER_MENU,
    INSTRUCTIONS_MENU,
    PLAYING,
} GameState;

struct sprite {
  uint16_t xpos, ypos;
  uint16_t height, width;
  uint32_t *colors_array;
  uint8_t is_pressed; 
};

struct position {
  uint16_t x,y;
};

typedef struct sprite sprite_t;
typedef struct watergirl watergirl_t;
typedef struct fireboy fireboy_t;
typedef struct position position_t;

struct gamecontext {
    Status gamestatus;
    GameState gamestate;
    sprite_t *mouse;
    sprite_t *play_button;
    sprite_t *quit_button;
    sprite_t *inst_button;
    sprite_t *multi_button;
    sprite_t *initial_screen_background;
    sprite_t *instructions_screen;
    sprite_t *back_button;
    sprite_t *game_screen;
    sprite_t *win_screen;
    sprite_t *boy;
    sprite_t *girl;
    sprite_t *wall;
    sprite_t *doors;
    char *map1;

    int numWalls;
    position_t* walls;
};

struct gamecontext context;



#endif
