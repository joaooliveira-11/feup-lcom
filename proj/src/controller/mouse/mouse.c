#include "mouse.h"

int mouse_hook_id = 2;
uint8_t mouse_current_byte;
uint8_t mouse_byte_index = 0;
uint8_t mouse_bytes[3];
struct packet mouse_packet;

int (mouse_subscribe_int)(uint8_t *bit_no){
    if(bit_no == NULL) return 1;
    *bit_no = BIT(mouse_hook_id);
    if(sys_irqsetpolicy(12, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != 0) return 1;
    return 0;
}

int(mouse_unsubscribe_int)(){
    if(sys_irqrmpolicy(&mouse_hook_id) != 0) return 1;
    return 0;
}

void (mouse_ih)(){
    if(read_KBC_output(0x60, &mouse_current_byte,1) != 0){
        printf("Error while reading a byte from mouse output\n");
    }
}


void (mouse_sync_bytes)(){
    if(mouse_byte_index == 0 && ( mouse_current_byte & BIT(3) ) ){   // bit 3 ativo é o byte de controlo, logo, começamos um packet
        mouse_bytes[mouse_byte_index] = mouse_current_byte;
        mouse_byte_index++;
    }
    else if(mouse_byte_index > 0){
        mouse_bytes[mouse_byte_index] = mouse_current_byte;
        mouse_byte_index++;
    }
}

void (mouse_bytes_to_packet)(){

    for(int x = 0 ;  x < 3; x++){
        mouse_packet.bytes[x] = mouse_bytes[x];
    }
    
    mouse_packet.lb = mouse_bytes[0] & BIT(0); // botão esq
    mouse_packet.mb = mouse_bytes[0] & BIT(2); // botão do meio
    mouse_packet.rb = mouse_bytes[0] & BIT(1); // botão dir

    mouse_packet.x_ov = mouse_bytes[0] & BIT(6); // overflow no deslocamento em x
    mouse_packet.y_ov = mouse_bytes[0] & BIT(7); // overflow no deslocamento em y

    mouse_packet.delta_x = (mouse_bytes[0] & BIT(4)) ? (0XFF00 | mouse_bytes[1]) : mouse_bytes[1]; // se o descolamento for negativo inverter para ter o valor absoluto
    mouse_packet.delta_y = (mouse_bytes[0] & BIT(5)) ? (0XFF00 | mouse_bytes[2]) : mouse_bytes[2];  // se o descolamento for negativo inverter para ter o valor absoluto
    // duvidoso 0xFF00 mas a lcf aceita
}

int (mouse_write)(uint8_t command){
    uint8_t attemps = 10;
    uint8_t mouse_answer;

    while(attemps && mouse_answer != ACK){
        if(write_KBC_command(0x64, 0xD4) != 0) return 1;
        if(write_KBC_command(0x60, command) != 0) return 1;  // comando direto para o rato com inibição da interpretação

        if(util_sys_inb(0x60, &mouse_answer) != 0) return 1;
        if(mouse_answer == ACK) return 0;
        tickdelay(micros_to_ticks(20000));
        attemps--;
    }
    return 1;
}
