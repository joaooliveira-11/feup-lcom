#include "keyboard.h"

uint8_t scancode = 0;
int keyboard_hook_id = 1;

int(read_KBC_status)(uint8_t * status){
    if(util_sys_inb(0x64, status) != 0) return 1;
    return 0;
}

int(write_KBC_command)(uint8_t port, uint8_t commandByte){
    uint8_t status;
    uint8_t attemps = 10;

    while(attemps){
        if(read_KBC_status(&status) != 0) return 1;
        if(!(status & BIT(1))){
            if(sys_outb(port, commandByte) != 0) return 1;
            return 0;
        }
        tickdelay(micros_to_ticks(20000));
        attemps--;
    }
    return 1;
}

int(read_KBC_output)(uint8_t port, uint8_t * output, uint8_t mouse_output){
    uint8_t status;
    uint8_t attemps = 10;

    while(attemps){
        if(read_KBC_status(&status) != 0) return 1;
        if(status & BIT(0)){
            if(util_sys_inb(port, output) != 0) return 1;
            if(status & (BIT(6) | BIT(7))) return 1;
            if(mouse_output && !(status & BIT(5))){
                printf("Mouse output expected but output is not from him\n");
                return 1;               
            }
            if(!mouse_output && (status & BIT(5))){
                printf("Keyboard output expected but output is not from him\n");
                return 1;
            }
            return 0;
        }
        tickdelay(micros_to_ticks(20000));
        attemps--;
    }
    return 1;
}

int(keyboard_subscribe_int)(uint8_t *mask){
    if(mask == NULL) return 1;
    *mask = BIT(keyboard_hook_id);
    if(sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id) != 0) return 1;
    return 0;
}

int(keyboard_unsubscribe_int)(){
    if(sys_irqrmpolicy(&keyboard_hook_id) != 0) return 1;
    return 0;
}


void(kbc_ih)(){
    if(read_KBC_output(0x60, &scancode,0) != 0) printf("error while reading scancode");
}

int (keyboard_restore)() {
    uint8_t commandByte;

    if (write_KBC_command(KBC_IN_CMD, KBC_READ_CMD) != 0) return 1;
    if (read_KBC_output(KBC_OUT_CMD, &commandByte,0) != 0) return 1;

    commandByte |= ENABLE_INT;

    if (write_KBC_command(KBC_IN_CMD, KBC_WRITE_CMD) != 0) return 1;
    if (write_KBC_command(KBC_WRITE_CMD, commandByte) != 0) return 1;

    return 0;
}

