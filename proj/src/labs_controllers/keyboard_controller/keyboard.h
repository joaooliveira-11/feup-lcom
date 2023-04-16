#ifndef KEYBOARD_
#define KEYBOARD_

#include <minix/sysutil.h>
#include "i8042.h"
#include <lcom/lcf.h>

int (read_KBC_status)(uint8_t* status);

int (read_KBC_output)(uint8_t port, uint8_t *output, uint8_t mouse_output);

int (write_KBC_command)(uint8_t port, uint8_t commandByte);

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

void (kbc_ih)();

int (keyboard_restore)();

#endif