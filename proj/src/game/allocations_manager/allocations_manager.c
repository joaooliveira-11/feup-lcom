#include "allocations_manager.h"

extern mouse_t mouse_packet;
extern struct gamecontext context;

void manage_game_allocations(){
    allocate_mouse();
    allocate_screens();
    allocate_game_elements();
    allocate_players();
    allocate_buttons();
}

void manage_game_deletes(){
    delete_screens();
    delete_game_elements();
    delete_players();
    delete_buttons();
}

void manage_start_states(){
    mouse_packet.xpos = 50;
    mouse_packet.ypos = 50;
    context.gamestatus = ON;
    context.gamestate = START_MENU; 

    context.levers_countdown = 0;
    context.startLeversCountdown = 0;

    context.map_countdown = 0;
    context.startMapCountdown = 1;
} 

