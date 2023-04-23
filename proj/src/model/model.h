#ifndef MODEL_H_
#define MODEL_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "../controller/util/KBC.h"
#include "../controller/mouse/mouse.h"
#include "../controller/graphics/graphics.h"
#include "sprite.h"
#include "../game_conf.h"

#include "xpm/hand.xpm"
#include "xpm/mouse.xpm"
#include "xpm/smile.xpm"
#include "view/view.h"


typedef enum {
    ON,
    OFF,
} SystemState;

typedef enum {
    START_MENU,
    //GAMEWIN_MENU,
    //GAMEOVER_MENU,
    //INSTRUCTIONS_MENU,
    PLAYING,
} GameState;

void prepare_sprites();
void delete_sprites();
void update_timer();
void update_keyboard();

#endif
