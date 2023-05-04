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

void set_sprite_xpos(sprite_t *sprite, uint16_t x){
    sprite->xpos = x;
}

void set_sprite_ypos(sprite_t *sprite, uint16_t y){
    sprite->ypos = y;
}
uint16_t get_sprite_xpos(sprite_t *sprite){
    return sprite->xpos;
}
uint16_t get_sprite_ypos(sprite_t *sprite){
    return sprite->ypos;
}

void (sprite_delete)(sprite_t * sprite){
    free(sprite->colors_array);
    free(sprite);
}
