#ifndef CONTEXT_H_
#define CONTEXT_H_

#define MAX_SPRITES 14

#define SPRITE_MOUSE_Idx 0
#define SPRITE_PLAYbtn_Idx 1
#define SPRITE_QUITbtn_Idx 2
#define SPRITE_INSTbtn_Idx 3
#define SPRITE_MULTIbtn_Idx 4
#define SPRITE_BACKbtn_Idx 5
#define SPRITE_INITscreen_Idx 6
#define SPRITE_INSTscreen_Idx 7
#define SPRITE_GAMEscreen_Idx 8
#define SPRITE_WINscree_Idx 9
#define SPRITE_BOY_Idx 10
#define SPRITE_GIRL_Idx 11
#define SPRITE_WALL_Idx 12
#define SPRITE_DOOR_Idx 13

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
  uint32_t *xpm;
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

    int numWalls;
    position_t* walls;
    sprite_t sprites[MAX_SPRITES];
};

struct gamecontext context;



#endif
