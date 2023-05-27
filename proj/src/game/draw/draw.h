#ifndef _LCOM_DRAW_H_
#define _LCOM_DRAW_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../../devices/graphics/graphics.h"
#include "../../devices/mouse/mouse.h"
#include "../interrupts_actions/interrupts.h"
#include "../context.h"
#include "../allocations_manager/allocations_manager.h"

int allocate_double_buffer(uint16_t mode);
void update_buffers();
void draw_frame();
void draw_initial_menu_screen();
void draw_instructions_menu_screen();
void draw_game_screen();
void draw_win_screen();
void draw_newMouse_pos();
int draw_movingSprite_xpm(sprite_t *sprite);
int draw_staticSprite_xpm(sprite_t *sprite, uint16_t x, uint16_t y);
void draw_lose_screen();
void draw_map();
void draw_timer_countDown();

typedef void (*funct_t)();
static funct_t funcs[] = {
    draw_initial_menu_screen,
    draw_win_screen,
    draw_lose_screen,
    draw_instructions_menu_screen,
    draw_game_screen,
};

#endif
