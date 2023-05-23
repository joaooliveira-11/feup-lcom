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
#include "xpms/players/running_left_boy.xpm"
#include "xpms/players/running_right_boy.xpm"
#include "xpms/players/watergirl.xpm"
#include "xpms/players/running_left_girl.xpm"
#include "xpms/players/running_right_girl.xpm"
#include "xpms/game_elements/wall.xpm"

void allocate_screens();
void allocate_game_elements();
void allocate_players();
void allocate_buttons();

void delete_screens();
void delete_game_elements();
void delete_players();
void delete_buttons();

#endif
