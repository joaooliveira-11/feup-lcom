#ifndef _KEYBOARD_PROJECT
#define _KEYBOARD_PROJECT

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../util/KBC.h"

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

void (kbc_ih)();

#endif
