#ifndef _MOUSE_PROJECT
#define _MOUSE_PROJECT

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../util/KBC.h"

typedef struct{
  uint8_t bytes[3]; 
  bool rb, mb, lb;  
  int16_t delta_x;  
  int16_t delta_y;
  bool x_ov, y_ov;
  uint16_t xpos;
  uint16_t ypos;
} mouse_t;

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (packet_bytes)();

void (build_mouse_packet)();

int (mouse_write_input)(uint8_t mouse_command);

#endif

