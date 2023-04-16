#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "i8042.h"
#include "i8254.h"
#include "KBC.c"
#include "mouse.h"
#include "timer.c"

extern uint8_t mouse_byte_index;
extern int timer_interrupts;
extern struct packet mouse_packet;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (mouse_test_packet)(uint32_t cnt){

    int ipc_status;
    message msg;
    uint8_t mouse_mask;
    uint32_t count_packets = cnt;

    if(mouse_subscribe_int(&mouse_mask) != 0) return 1;
    if(mouse_write(0xF4) != 0) return 1;

    while(count_packets) {

    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: 
          if (msg.m_notify.interrupts & mouse_mask){  
            mouse_ih();                               
            mouse_sync_bytes();                       
            if (mouse_byte_index == 3) {             
              mouse_bytes_to_packet();
              mouse_byte_index = 0;
              count_packets--;      
              mouse_print_packet(&mouse_packet);     
            }
          }
          break;
      }
    }
  }

  if(mouse_write(0xF5) != 0) return 1;
  if(mouse_unsubscribe_int() != 0) return 1;
  return 0;
}

int (mouse_test_async)(uint8_t idle_time){

    uint8_t seconds_without_packets = 0;
    int ipc_status;
    message msg;
    uint8_t timer_mask, mouse_mask;
    uint32_t timer_interrupt_freq = sys_hz();

    if(mouse_subscribe_int(&mouse_mask) != 0) return 1;
    if(timer_subscribe_int(&timer_mask) != 0) return 1;

    if(mouse_write(0xF4) != 0) return 1;

    while(seconds_without_packets != idle_time) {

    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          
          if (msg.m_notify.interrupts & timer_mask) {
            timer_int_handler();
            if (timer_interrupts % timer_interrupt_freq == 0) seconds_without_packets++;
          }

          if (msg.m_notify.interrupts & mouse_mask){  
            mouse_ih();                               
            mouse_sync_bytes();                       
            if (mouse_byte_index == 3) {             
              mouse_bytes_to_packet();
              mouse_byte_index = 0;   
              mouse_print_packet(&mouse_packet);     
            }
            seconds_without_packets = 0;
            timer_interrupts = 0;
          }
          break;
      }
    }
  }

  if(mouse_unsubscribe_int() != 0) return 1;
  if(timer_unsubscribe_int() != 0) return 1;
  if(mouse_write(0xF5) != 0) return 1;

  return 0;
}

