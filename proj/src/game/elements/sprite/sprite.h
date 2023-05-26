#ifndef SPRITE_H
#define SPRITE_H

#include "../../../devices/graphics/graphics.h"
#include "../../context.h"
#include <lcom/lcf.h>


sprite_t *(sprite_build)(xpm_map_t xpm);

int sprite_build1(sprite_t* sprite, xpm_map_t xpm_);

void (sprite_delete)(sprite_t * sprite);


void set_sprite_xpos(sprite_t *sprite, uint16_t x);
void set_sprite_ypos(sprite_t *sprite, uint16_t y);
uint16_t get_sprite_xpos(sprite_t *sprite);
uint16_t get_sprite_ypos(sprite_t *sprite);



#endif
