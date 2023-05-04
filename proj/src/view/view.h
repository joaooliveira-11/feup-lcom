#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../controller/graphics/graphics.h"
#include "../controller/mouse/mouse.h"
#include "../model/sprite.h"
#include "../model/model.h"

void draw_frame();
void draw_initial_menu_screen();
void draw_instructions_menu_screen();
void draw_game_screen();
void draw_newMouse_pos();
void buffer_swap();
int draw_movingSprite_xpm(sprite_t *sprite);
int draw_staticSprite_xpm(sprite_t *sprite, uint16_t x, uint16_t y);
int allocate_double_buffer(uint16_t mode);
void check_mouse_clicks();

#endif
