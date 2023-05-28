#ifndef _TIMER_PROJECT
#define _TIMER_PROJECT

#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

#define BIT(n) (1 << (n))

int (timer_set_frequency)(uint8_t timer, uint32_t freq);

int (timer_get_conf)(uint8_t timer, uint8_t *st);

int (timer_subscribe_int)(uint8_t *bit_no);

int (timer_unsubscribe_int)();

#endif
