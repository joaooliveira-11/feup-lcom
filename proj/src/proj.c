#include <lcom/lcf.h>
#include "controller/timer/timer.h"
#include "controller/graphics/graphics.h"
#include "controller/keyboard/keyboard.h"
#include "controller/mouse/mouse.h"
#include "game_conf.h"
#include "view/view.h"
#include "model/model.h"

uint8_t TIMER_MASK, KEYBOARD_MASK, MOUSE_MASK;
extern SystemState systemstate;
extern mouse_t mouse_packet;

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/proj/src/debug/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/src/debug/output.txt");
  if(lcf_start(argc, argv)) return 1;
  lcf_cleanup();

  return 0;
}

void(prepare_menus)(){
  create_menu_sprites();
  create_menu_buttons();
  create_instructions_sprites();
  create_instructions_buttons();
}

void(prepare_game)(){
  create_game_sprites();
  //create_game_buttons();
}

void(prepare_mouse)(){
  create_mouse_sprite();
}

void(delete_menus)(){
  create_menu_sprites();
  create_menu_buttons();
  create_instructions_sprites();
  create_instructions_buttons();
}

void(delete_game)(){
  delete_game_sprites();
  //delete_game_buttons();
}

void(delete_mouse)(){
  delete_mouse_sprite();
}

int (prepare_project)(){

    if(timer_set_frequency(0, GAMEFPS) != 0) return 1;
    if(changeTo_graphic_mode(GAME_MODE) != 0) return 1;
    if(allocate_double_buffer(GAME_MODE) != 0) return 1;

    prepare_menus();
    prepare_game();
    prepare_mouse();
    
    if(mouse_write(0xEA) != 0) return 1; // enable steam mode
    if(mouse_write(0xF4) != 0) return 1; // enable data report


    // Ativar Interrupções
    if(timer_subscribe_int(&TIMER_MASK) != 0) return 1;
    if(keyboard_subscribe_int(&KEYBOARD_MASK) != 0) return 1;
    if(mouse_subscribe_int(&MOUSE_MASK) != 0) return 1;

    mouse_packet.xpos = 50;
    mouse_packet.ypos = 50;
    return 0;
}

int (finish_project)(){

  if(vg_exit() != 0) return 1;

  delete_menus();
  delete_game();
  delete_mouse();

  // Desativar Interrupções
  if(timer_unsubscribe_int() != 0) return 1;
  if(keyboard_unsubscribe_int() != 0) return 1;
  if(mouse_unsubscribe_int() != 0) return 1;

  if (mouse_write(0xF5) != 0) return 1;  // disable data report

  return 0;
}

int (proj_main_loop)(int argc, char *argv[]) {

  if(prepare_project() != 0){
    if(finish_project() != 0) return 1;
    return 0;
  }

  draw_frame();

  int ipc_status;
  message msg;
  while (systemstate == ON) {
    
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & TIMER_MASK)    update_timer();
          if (msg.m_notify.interrupts & KEYBOARD_MASK) update_keyboard();
          if (msg.m_notify.interrupts & MOUSE_MASK) update_mouse();
        }
    }
  }
  
  if(finish_project() != 0) return 1;

  return 0;
}

