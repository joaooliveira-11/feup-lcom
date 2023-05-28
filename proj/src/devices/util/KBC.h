#ifndef _LCOM_KBC_MOUSE_KEYBOARD_H_
#define _LCOM_KBC_MOUSE_KEYBOARD_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#define BIT(n) (1 << (n))

int(reading_KBC_STATE)(uint8_t * state);
int(write_KBC_INPUT)(uint8_t port, uint8_t kbc_command);

int(read_KBC_keyboardOUTPUT)(uint8_t port, uint8_t * kbc_output);
int(read_KBC_mouseOUTPUT)(uint8_t port, uint8_t * kbc_output);

#endif
