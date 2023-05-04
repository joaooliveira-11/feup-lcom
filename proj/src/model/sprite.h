#ifndef SPRITE_H
#define SPRITE_H


#include <lcom/lcf.h>
#include "../controller/graphics/graphics.h"

struct sprite {
  uint16_t xpos, ypos;
  uint16_t height, width;
  uint32_t *colors_array;
  uint32_t main_color; 
  uint8_t is_pressed; 
};

typedef struct sprite sprite_t;


sprite_t *(sprite_build)(xpm_map_t xpm);
void (sprite_delete)(sprite_t * sprite);


void set_sprite_xpos(sprite_t *sprite, uint16_t x);
void set_sprite_ypos(sprite_t *sprite, uint16_t y);
uint16_t get_sprite_xpos(sprite_t *sprite);
uint16_t get_sprite_ypos(sprite_t *sprite);

#endif
