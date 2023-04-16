#include "KBC.h"

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