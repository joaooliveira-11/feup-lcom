#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../controller/graphics/graphics.h"
#include "../controller/mouse/mouse.h"
#include "../model/sprite.h"
#include "../model/model.h"

void draw_new_frame();
void draw_initial_menu();
void draw_game_menu();
void swap_buffers();
int draw_sprite_xpm(sprite_t *sprite, int x, int y);
int draw_sprite_button(sprite_t *sprite, int x, int y);
int set_frame_buffers(uint16_t mode);

#endif
