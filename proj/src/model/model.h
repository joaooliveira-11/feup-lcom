#ifndef MODEL_H_
#define MODEL_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "../controller/util/KBC.h"
#include "../controller/mouse/mouse.h"
#include "../controller/graphics/graphics.h"
#include "sprite.h"
#include "../game_conf.h"

#include "xpm/mouse.xpm"
#include "xpm/background_final.xpm"
#include "xpm/instructions.xpm"
#include "xpm/button_inst.xpm"
#include "xpm/button_multi.xpm"
#include "xpm/button_play.xpm"
#include "xpm/button_quit.xpm"
#include "xpm/button_back.xpm"
#include "xpm/game_backgroung.xpm"
#include "xpm/fireboy.xpm"
#include "xpm/running_left_boy.xpm"
#include "xpm/running_right_boy.xpm"
#include "xpm/watergirl.xpm"
#include "xpm/running_left_girl.xpm"
#include "xpm/running_right_girl.xpm"

#include "view/view.h"


typedef enum {
    ON,
    OFF,
} SystemState;

typedef enum {
    START_MENU,
    //GAMEWIN_MENU,
    //GAMEOVER_MENU,
    INSTRUCTIONS_MENU,
    PLAYING,
} GameState;


void create_mouse_sprite();

void create_menu_sprites();
void create_menu_buttons();

void create_instructions_sprites();
void create_instructions_buttons();

void create_game_sprites();
void create_game_buttons();

void delete_mouse_sprite();

void delete_menu_sprites();
void delete_menu_buttons();

void delete_instructions_sprites();
void delete_instructions_buttons();

void delete_game_sprites();
void delete_game_buttons();

void update_timer();
void update_keyboard();
void update_mouse();

#endif
