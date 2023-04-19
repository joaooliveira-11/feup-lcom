#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "keyboard.h"
#include "timer.c"
#include <lcom/pixmap.h>


extern uint8_t scancode;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if(changeTo_graphic_mode(mode) != 0) return 1;
  sleep(delay);
  if(vg_exit() != 0) return 1;
  return 0;
}

int (quit_draw)() {

  int ipc_status;
  message msg;
  uint8_t keyboard_mask;

  if (keyboard_subscribe_int(&keyboard_mask) != 0) return 1;

  while (scancode != BREAK_ESC){
    if (driver_receive(ANY, &msg, &ipc_status) != 0) { 
      printf("driver_receive failed");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & keyboard_mask) 
            kbc_ih();
            break;
        default:
          break; 
      }
    }
  }

  if (keyboard_unsubscribe_int() != 0) return 1;
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  if(frame_buffer_build(mode) != 0) return 1;
  if(changeTo_graphic_mode(mode) != 0) return 1;

  uint32_t fixed_color;
  if(fix_colorMode_bits(color, &fixed_color) != 0) return 1;

  if(draw_rectangle(x, y, width, height, fixed_color) != 0) return 1;
  if (quit_draw() != 0) return 1;
  if (vg_exit() != 0) return 1;
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if(frame_buffer_build(mode) != 0) return 1;
  if(changeTo_graphic_mode(mode) != 0) return 1;

  if(video_pattern(no_rectangles, first, step) != 0) return 1;

  if (quit_draw() != 0) return 1;
  if (vg_exit() != 0) return 1;

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if(frame_buffer_build(0x105) != 0) return 1;
  if(changeTo_graphic_mode(0x105) != 0) return 1;

  if (print_xpm(xpm, x, y) != 0) return 1;

  if (quit_draw() != 0) return 1;
  if (vg_exit() != 0) return 1;

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  int ipc_status;
  message msg;
  uint8_t timer_mask, keyboard_mask; // máscaras para as interrupções

  // o movimento só pode ser horizontal ou vertical
  uint8_t vertical_direction;
  if (xi == xf && yi < yf) vertical_direction = 1;
  else if (yi == yf && xi < xf) vertical_direction = 0;
  else return 1;


  if (keyboard_subscribe_int(&keyboard_mask) != 0) return 1;
  if (timer_subscribe_int(&timer_mask) != 0) return 1;

  if (timer_set_frequency(0, fr_rate) != 0) return 1;   

  if(frame_buffer_build(0x105)) return 1;

  if(changeTo_graphic_mode(0x105)) return 1; 

  if (print_xpm(xpm, xi, yi) != 0) return 1;

  while (scancode != BREAK_ESC && (xi < xf || yi < yf)) {

      if( driver_receive(ANY, &msg, &ipc_status) != 0 ){
          printf("Error");
          continue;
      }

      if(is_ipc_notify(ipc_status)) {
          switch(_ENDPOINT_P(msg.m_source)){
              case HARDWARE:

                if (msg.m_notify.interrupts & keyboard_mask) {
                    kbc_ih();
                }

                if (msg.m_notify.interrupts & timer_mask) {

                    if (draw_rectangle(xi, yi, 100, 100, 0xFFFFFF) != 0) return 1;

                    if (vertical_direction) {
                        yi += speed;
                        if (yi > yf) yi = yf;
                    } else {
                        xi += speed;
                        if (xi > xf) xi = xf;
                    }

                    if (print_xpm(xpm, xi, yi) != 0) return 1;
                }
          }
      }
  }

  if (vg_exit() != 0) return 1;

  if (timer_unsubscribe_int() != 0) return 1;
  if (keyboard_unsubscribe_int() != 0) return 1;

  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}


