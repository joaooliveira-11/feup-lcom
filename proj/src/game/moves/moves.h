#ifndef MOVESH
#define MOVESH

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "../interrupts_actions/interrupts.h"

int check_FBmoveUP();
int check_FBmoveDOWN();
int check_FBmoveRIGHT();
int check_FBmoveLEFT();

int check_WGmoveUP();
int check_WGmoveDOWN();
int check_WGmoveRIGHT();
int check_WGmoveLEFT();

void move_FBup();
void move_FBdown();
void move_FBright();
void move_FBleft();

void move_WGup();
void move_WGdown();
void move_WGright();
void move_WGleft();

void mouse_MENU();
void mouse_INSTRUCTIONS();
void mouse_PLAYING();
void mouse_GAMEOVER();
void mouse_GAMEWIN();

int check_colisions(uint16_t targetXPOS, uint16_t targetYPOS, int PlayerType);
void check_mouse_clicks();
void check_gameWin();
int check_nearBY(lever_t lever, int PlayerType);

void reset_barrier();
void reset_mouseClicks();


typedef void (*funct1_t)();
static funct1_t funcs1[] = {
    mouse_MENU,
    mouse_GAMEWIN,
    mouse_GAMEOVER,
    mouse_INSTRUCTIONS,
    mouse_PLAYING,
};

#endif
