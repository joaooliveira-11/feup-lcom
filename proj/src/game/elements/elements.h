#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "../../devices/util/KBC.h"
#include "../../devices/mouse/mouse.h"
#include "../../devices/graphics/graphics.h"
#include "sprite/sprite.h"
#include "../draw/draw.h"
#include "../context.h"

#include "xpms/game_elements/mouse.xpm"
#include "xpms/screens/background_final.xpm"
#include "xpms/screens/instructions.xpm"
#include "xpms/buttons/button_inst.xpm"
#include "xpms/buttons/button_multi.xpm"
#include "xpms/buttons/button_play.xpm"
#include "xpms/buttons/button_quit.xpm"
#include "xpms/buttons/button_back.xpm"
#include "xpms/screens/game_backgroung.xpm"
#include "xpms/players/fireboy.xpm"
#include "xpms/players/watergirl.xpm"
#include "xpms/game_elements/wall.xpm"
#include "xpms/game_elements/doors.xpm"
#include "xpms/screens/wonMenu.xpm"
#include "xpms/game_elements/barrier.xpm"
#include "xpms/game_elements/lever_left.xpm"
#include "xpms/game_elements/lever_right.xpm"
#include "xpms/game_elements/fire.xpm"
#include "xpms/game_elements/ice.xpm"
#include "xpms/screens/lostMenu.xpm"
#include "xpms/buttons/button_mainMenu.xpm"

static char **xpms_array[] = {
    mouse_xpm,
    button_play_xpm,
    button_quit_xpm,
    button_inst_xpm,
    button_multi_xpm,
    button_back_xpm,
    button_mainMenu_xpm,
    background_final_xpm,
    instructions_xpm,
    game_backgroung_xpm,
    wonMenu_xpm,
    lostMenu_xpm,
    fireboy_xpm,
    watergirl_xpm,
    wall_xpm,
    doors_xpm,
    barrier_xpm,
    lever_left_xpm,
    lever_right_xpm,
    fire_xpm,
    ice_xpm
};

int read_map();
void allocate_mouse();
void allocate_screens();
void allocate_game_elements();
void allocate_players();
void allocate_buttons();

void delete_screens();
void delete_game_elements();
void delete_players();
void delete_buttons();

#endif
