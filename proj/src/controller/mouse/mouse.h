#ifndef MOUSE_H_
#define MOUSE_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../util/KBC.h"

typedef struct{
  uint8_t bytes[3]; // mouse packet raw bytes
  bool rb, mb, lb;  // right, middle and left mouse buttons pressed
  int16_t delta_x;  // mouse x-displacement: rightwards is positive
  int16_t delta_y;  // mouse y-displacement: upwards is positive
  bool x_ov, y_ov;  // mouse x-displacement and y-displacement overflows
  uint16_t xpos;
  uint16_t ypos;
} mouse_t;

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (mouse_sync_bytes)();

void (mouse_bytes_to_packet)();

int (mouse_write)(uint8_t command);

#endif

