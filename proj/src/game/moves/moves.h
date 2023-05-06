#ifndef MOVES_H_
#define MOVES_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "../interrupts_actions/interrupts.h"


int check_arena_border(uint16_t sprite_initialX, uint16_t sprite_finalX, uint16_t sprite_initialY, uint16_t sprite_finalY);
void check_mouse_clicks();

#endif
