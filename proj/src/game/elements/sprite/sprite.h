#ifndef SPRITE_H
#define SPRITE_H

#include "../../../devices/graphics/graphics.h"
#include <lcom/lcf.h>


struct sprite {
  uint16_t xpos, ypos;
  uint16_t height, width;
  uint32_t *colors_array;
  uint8_t is_pressed; 
};

struct watergirl {
  uint16_t xpos, ypos;
  uint16_t type; // 0 - up/down , 1 - left, 2 right
};

struct fireboy {
  uint16_t xpos, ypos;
  uint16_t type; // 0 - up/down , 1 - left, 2 right
};

typedef struct sprite sprite_t;
typedef struct watergirl watergirl_t;
typedef struct fireboy fireboy_t;


sprite_t *(sprite_build)(xpm_map_t xpm);
void (sprite_delete)(sprite_t * sprite);


void set_sprite_xpos(sprite_t *sprite, uint16_t x);
void set_sprite_ypos(sprite_t *sprite, uint16_t y);
uint16_t get_sprite_xpos(sprite_t *sprite);
uint16_t get_sprite_ypos(sprite_t *sprite);



#endif
