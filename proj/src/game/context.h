#ifndef CONTEXT_H_
#define CONTEXT_H_

typedef enum {
    ON,
    OFF,
} Status;

typedef enum {
    START_MENU,
    //GAMEWIN_MENU,
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

struct watergirl {
  uint16_t xpos, ypos;
  uint16_t type; // 0 - up/down , 1 - left, 2 right
};

struct fireboy {
  uint16_t xpos, ypos;
  uint16_t type; // 0 - up/down , 1 - left, 2 right
};

typedef struct sprite sprite_t;
typedef struct watergirl watergirl_t;
typedef struct fireboy fireboy_t;

struct gamecontext {
    //vbe_mode_info_t vbe_mode_info;
    Status gamestatus;
    GameState gamestate ;
    //mouse_t mouse_packet;
    sprite_t *mouse;
    sprite_t *play_button;
    sprite_t *quit_button;
    sprite_t *inst_button;
    sprite_t *multi_button;
    sprite_t *initial_screen_background;
    sprite_t *instructions_screen;
    sprite_t *back_button;
    sprite_t *game_screen;
    sprite_t *boy;
    sprite_t *girl;
    sprite_t *boy_left;
    sprite_t *boy_right;
    sprite_t *girl_left;
    sprite_t *girl_right;
    sprite_t *wall;
    watergirl_t watergirl;
    fireboy_t fireboy;
    char *map1;
};

struct gamecontext context;



#endif
