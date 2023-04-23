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
sprite_t *create_sprite_button(uint16_t width, uint16_t height, uint32_t color);
void (sprite_delete)(sprite_t * sprite);

#endif
