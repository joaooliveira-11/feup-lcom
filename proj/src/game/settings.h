#define GAMEFPS 60 
#define GAME_MODE 0x115
#define TRANSPARENT 0xFFFFFE

//#define INITIAL_MENU  31
#define GAME_SCREEN   34
#define QUIT          16

#define W 0x11
#define A 0x1e
#define S 0x1f
#define D 0x20

#define arrowup 0x48
#define arrowleft 0x4b 
#define arrowdown 0x50
#define arrowright 0x4d

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

