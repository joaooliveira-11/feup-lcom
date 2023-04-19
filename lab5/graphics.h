#ifndef LCOM_GRAPHICS_CARD_H
#define LCOM_GRAPHICS_CARD_H

#include <lcom/lcf.h>

#define VBE_768p_INDEXED 0x105
#define VBE_480p_DC 0x110
#define VBE_600p_DC 0x115
#define VBE_1024p_DC 0x11A
#define VBE_864p_DC 0x14C

#define VBE_MODE_SET 0x4F02
#define VBE_LINEAR_FB BIT(14)

#define DIRECT_COLOR 0x06
#define INDEXED_COLOR 0x105

#define BIOS_SET_VIDEOMODE 0x00
#define BIOS_VIDEOCARD_SERV 0x10

int (changeTo_graphic_mode)(uint16_t submode);

int (changeTo_text_mode)();

int (frame_buffer_build)(uint16_t mode);

int (color_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (draw_horizontal_line)(uint16_t x, uint16_t y, uint16_t length, uint32_t color);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (fix_colorMode_bits)(uint32_t color, uint32_t *color_fix);

uint32_t(direct_color)(uint32_t red_, uint32_t green_, uint32_t blue_);
uint32_t(indexed_color)(uint16_t col, uint16_t row, uint8_t step, uint32_t first, uint8_t no_rectangles);

uint32_t(R_first)(uint32_t first);
uint32_t(G_first)(uint32_t first);
uint32_t(B_first)(uint32_t first);

uint32_t(R)(unsigned col, uint8_t step, uint32_t first);
uint32_t(G)(unsigned row, uint8_t step, uint32_t first);
uint32_t(B)(unsigned row, unsigned col, uint8_t step, uint32_t first);

int(video_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step);

int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);
#endif

