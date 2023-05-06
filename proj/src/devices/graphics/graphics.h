#ifndef LCOM_GRAPHICS_CARD_H
#define LCOM_GRAPHICS_CARD_H

#include <lcom/lcf.h>
#include "VBE.h"

vbe_mode_info_t vbe_mode_info;

int (changeTo_graphic_mode)(uint16_t submode);

int (frame_buffer_build)(uint16_t mode, uint8_t** frame_buffer);

int (color_pixel)(uint16_t x, uint16_t y, uint32_t color, uint8_t* frame_buffer);

int (draw_horizontal_line)(uint16_t x, uint16_t y, uint16_t length, uint32_t color, uint8_t * frame_buffer);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint8_t* frame_buffer);


#endif
