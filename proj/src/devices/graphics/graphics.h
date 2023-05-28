#ifndef _GRAPHICS_PROJECT
#define _GRAPHICS_PROJECT

#include <lcom/lcf.h>

vbe_mode_info_t vbe_mode_info;

int (changeTo_graphic_mode)(uint16_t submode);

int (frame_buffer_build)(uint16_t mode, uint8_t** frame_buffer);

int (color_pixel)(uint16_t x, uint16_t y, uint32_t color, uint8_t* frame_buffer);

#endif
