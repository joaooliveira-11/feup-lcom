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
int draw_sprite_xpm(sprite_t *sprite);
int draw_sprite_button(sprite_t *sprite, int x, int y);
int allocate_double_buffer(uint16_t mode);
void check_mouse_clicks();
#endif
