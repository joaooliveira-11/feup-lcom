#include "sprite.h"

sprite_t *(sprite_build)(xpm_map_t xpm){

    sprite_t *sprite = (sprite_t *) malloc(sizeof(sprite_t));
    if(sprite == NULL) return NULL;

    xpm_image_t img;
    sprite->colors_array = (uint32_t *) xpm_load(xpm, XPM_8_8_8_8, &img);
    if(sprite->colors_array == NULL){
        free(sprite);
        return NULL;
    }

    sprite->height = img.height;
    sprite->width = img.width;

    return sprite;
}

sprite_t *create_sprite_button(uint16_t width, uint16_t height, uint32_t color){
  sprite_t *sprite = (sprite_t *) malloc(sizeof(sprite_t));
  sprite->height = height;
  sprite->width = width;
  sprite->colors_array = NULL;
  sprite->main_color = color;
  sprite->is_pressed = 0;
  return sprite;
}


void (sprite_delete)(sprite_t * sprite){
    free(sprite->colors_array);
    free(sprite);
}
