#include "rtc.h"

int rtc_hook_id = RTC_MASK;
int interrupts = 0;
uint8_t binary_mode;
rtc_info time_info;


int (rtc_output)(uint8_t command, uint8_t *output){
    if (sys_outb(INPUT_REG, command) != 0) return 1;
    if(util_sys_inb(OUTPUT_REG, output) != 0) return 1;
    return 0;
}

int (rtc_busy)(){
    uint8_t res;
    if (rtc_output(REGISTER_UPDATING, &res)) return 1;
	return res & UPDATING;
}

int (rtc_check_output)(){
    uint8_t output;
    if ((rtc_output(SEC, &output) != 0 ) || (rtc_output(MIN_t, &output) != 0) || (rtc_output(H, &output) != 0) || (rtc_output(D_t, &output) != 0) || (rtc_output(M, &output) != 0) || (rtc_output(Y, &output) != 0)) return 1;
    return 0;
}

int (rtc_update_time)(){

    if (rtc_busy() != 0) return 1;
    if (rtc_check_output() != 0) return 1;

    uint8_t output;
    rtc_output(SEC, &output);
    time_info.seconds = binary_mode ? output : rtc_to_bin(output);
    rtc_output(MIN_t, &output);
    time_info.minutes = binary_mode ? output : rtc_to_bin(output);
    rtc_output(H, &output);
    time_info.hours = binary_mode ? output : rtc_to_bin(output);
    rtc_output(D_t, &output);
    time_info.day = binary_mode ? output : rtc_to_bin(output);
    rtc_output(M, &output);
    time_info.month = binary_mode ? output : rtc_to_bin(output);
    rtc_output(Y, &output);
    time_info.year = binary_mode ? output : rtc_to_bin(output);

    return 0;
}

int (rtc_subscribe_int)(uint8_t *bit){
    if(bit == NULL) return 1;
    return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &rtc_hook_id);
}

int (rtc_unsubscribe_int)(){
    return sys_irqrmpolicy(&rtc_hook_id);
}

void (refresh_timer)(){
    interrupts++;
}

void (refresh_rtc)(){
    if(interrupts % 60 == 0) refresh_timer();
}

int (rtc_check_binary)(){
    return !rtc_check_bcd();
}

int (rtc_check_bcd)(){
    uint8_t status;
    if(rtc_output(REGISTER_COUNTING, &status)) return 1;
        return !(status & BINARY);
}

uint8_t (rtc_to_bin)(uint8_t number){
    return ((number >> 4) * 10) + (number & 0xF);
}

void (rtc_setup)(){
    rtc_update_time();
    binary_mode = rtc_check_binary();
}
