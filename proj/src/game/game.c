#include "game.h"
#include <lcom/lcf.h>
#include "../devices/timer/timer.h"
#include "../devices/graphics/graphics.h"
#include "../devices/keyboard/keyboard.h"
#include "../devices/mouse/mouse.h"
#include "interrupts_actions/interrupts.h"


extern mouse_t mouse_packet;
extern uint8_t TIMER_MASK, KEYBOARD_MASK, MOUSE_MASK;

int(start_game)(){
    if(timer_set_frequency(0, GAMEFPS) != 0) return 1;
    if(changeTo_graphic_mode(GAME_MODE) != 0) return 1;
    if(allocate_double_buffer(GAME_MODE) != 0) return 1;

    allocate_screens();
    allocate_game_elements();
    allocate_players();
    allocate_buttons();
    
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


int(finish_game)(){
  if(vg_exit() != 0) return 1;

  delete_screens();
  delete_buttons();
  delete_game_elements();
  delete_players();

  // Desativar Interrupções
  if(timer_unsubscribe_int() != 0) return 1;
  if(keyboard_unsubscribe_int() != 0) return 1;
  if(mouse_unsubscribe_int() != 0) return 1;

  if (mouse_write(0xF5) != 0) return 1;  // disable data report

  return 0;
}

