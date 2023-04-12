#include <lcom/lab3.h>
#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "KBC.c"
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"


extern uint32_t counter_sysinb;
extern int counter;
extern uint8_t scancode;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {

  int ipc_status;
  uint8_t keyboard_mask;
  message msg;
  bool twobytes_scancode = false;

  if (keyboard_subscribe_int(&keyboard_mask) != 0) return 1;
  while (scancode != BREAK_ESC) {

    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & keyboard_mask) {
            kbc_ih();
            if (scancode == TWO_BYTES) {
              twobytes_scancode = true;
            }
            else {
              if (twobytes_scancode) {
                uint8_t scancode_bytes[2] = {TWO_BYTES, scancode};
                kbd_print_scancode(!(scancode & MAKE_CODE), 2, scancode_bytes);
              }
              else {
                kbd_print_scancode(!(scancode & MAKE_CODE), 1, &scancode);
              }
              twobytes_scancode = false;
            }
          }
      }
    }
  }

  if (keyboard_unsubscribe_int() != 0) return 1;
  return 0;
}

int(kbd_test_poll)() {
    bool twobytes_scancode = false;
    
  while (scancode != BREAK_ESC) {
    if (read_KBC_output(0x60, &scancode) == 0) {
      if (scancode == TWO_BYTES) {
        twobytes_scancode = true;
      }
      else {
        if (twobytes_scancode) {
          uint8_t scancode_bytes[2] = {TWO_BYTES, scancode};
          kbd_print_scancode(!(scancode & MAKE_CODE), 2, scancode_bytes);
        }
        else {
          kbd_print_scancode(!(scancode & MAKE_CODE), 1, &scancode);
        }
        twobytes_scancode = false;
      }
    }
  }

  if (keyboard_restore() != 0) return 1;
  if (kbd_print_no_sysinb(counter_sysinb) != 0) return 1;
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status;
  uint8_t keyboard_mask, timer_mask;
  message msg;
  bool twobytes_scancode = false;
  int count_seconds = 0; 
  
  if(timer_subscribe_int(&timer_mask) != 0) return 1;
  if(keyboard_subscribe_int(&keyboard_mask) != 0) return 1;

  while (scancode != BREAK_ESC && count_seconds < n) {

    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & keyboard_mask) {
            kbc_ih();
            count_seconds = 0;
            counter = 0;
            if (scancode == TWO_BYTES) {
              twobytes_scancode = true;
            }
            else {
              if (twobytes_scancode) {
                uint8_t scancode_bytes[2] = {TWO_BYTES, scancode};
                kbd_print_scancode(!(scancode & MAKE_CODE), 2, scancode_bytes);
              }
              else {
                kbd_print_scancode(!(scancode & MAKE_CODE), 1, &scancode);
              }
              twobytes_scancode = false;
            }
          }
          if(msg.m_notify.interrupts & timer_mask){
            timer_int_handler();
            if(counter % 60 == 0) count_seconds++;
          }
      }
    }
  }
  if (timer_unsubscribe_int() != 0) return 1;
  if (keyboard_unsubscribe_int() != 0) return 1;
  return 0;
}