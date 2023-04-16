#include "timer.h"

int timer_hook_id = 0;
int timer_interrupts = 0;


int(timer_set_frequency)(uint8_t timer, uint32_t freq){
  if(timer < 0 || timer > 2 || freq < 19 || freq > TIMER_FREQ) return 1;

  uint16_t initialvalue = TIMER_FREQ / freq;
  uint8_t lsb, msb;
  if(util_get_LSB(initialvalue, &lsb) != 0) return 1;
  if(util_get_MSB(initialvalue, &msb) != 0) return 1;

  uint8_t controlword;
  if(timer_get_conf(timer, &controlword) != 0) return 1;
  controlword = (controlword & 0x0F) | BIT(4) | BIT(5);
  switch(timer){
    case 0: 
      break;

    case 1:
      controlword |= BIT(6);
      break;
    
    case 2:
      controlword |= BIT(7);
      break;

    default:
      return 1;
  }
  if(sys_outb(0x43, controlword) != 0) return 1;
  if(sys_outb(0x40 + timer, lsb) != 0) return 1;
  if(sys_outb(0x40 + timer, msb) != 0) return 1;
  return 0;
}

int(timer_subscribe_int)(uint8_t *mask){
  if(mask == NULL) return 1;
  *mask = BIT(timer_hook_id);
  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != 0) return 1;
  return 0;
}

int(timer_unsubscribe_int)(){
  if(sys_irqrmpolicy(&timer_hook_id) != 0) return 1;
  return 0;
}

void(timer_int_handler)(){
  timer_interrupts++;
}

int(timer_get_conf)(uint8_t timer, uint8_t *st){
  if(st == NULL) return 1;
  uint32_t controlword = BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1);
  if(sys_outb(0x43, controlword) != 0) return 1;
  if(util_sys_inb(0x40 + timer, st) != 0) return 1;
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field){
  union timer_status_field_val data;
  
  switch(field){
    case tsf_all:
      data.byte = st;
      break;

    case tsf_initial:
      st =  st >> 4;
      st = st & 0x03;
      if(st == 1) data.in_mode = LSB_only;
      else if(st == 2) data.in_mode = MSB_only;
      else if (st == 3) data.in_mode = MSB_after_LSB;
      break;

    case tsf_mode:
      st = st >> 1;
      st = st & 0x07;
      if(st == 7) data.count_mode = 3;
      else if(st == 6) data.count_mode = 2;
      else data.count_mode = st;
      break;

    case tsf_base:
      data.bcd = st & 0x01;
      break;
    
    default:
      return 1;
  }
  if(timer_print_config(timer,field,data) != 0) return 1;
  return 0;
}