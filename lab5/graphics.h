#ifndef LCOM_GRAPHICS_CARD_H
#define LCOM_GRAPHICS_CARD_H

#include <lcom/lcf.h>

int (changeTo_graphic_mode)(uint16_t submode);

int (changeTo_text_mode)();

int (frame_buffer_build)(uint16_t mode);

int (color_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (draw_horizontal_line)(uint16_t x, uint16_t y, uint16_t length, uint32_t color);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);



#endif

