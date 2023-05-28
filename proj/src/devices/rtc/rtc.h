#ifndef _LCOM_RTCH
#define _LCOM_RTCH

#include <minix/sysutil.h>
#include <lcom/lcf.h>


#define RTC_MASK            4
#define IRQ_RTC             8
#define INPUT_REG           0x70
#define OUTPUT_REG          0x71
#define REGISTER_UPDATING   10
#define REGISTER_COUNTING   11
#define SEC        0
#define MIN_t      2
#define H          4
#define D_t        7
#define M          8
#define Y          9
#define BINARY              BIT(2)
#define UPDATING            BIT(7)


typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} rtc_info;



void (rtc_setup)();
int (rtc_subscribe_int)(uint8_t *bit);
int (rtc_unsubscribe_int)();
int (rtc_output)(uint8_t command, uint8_t *output);
int (rtc_busy)();
int (rtc_check_binary)();
int (rtc_check_bcd)();
int (rtc_update_time)();
uint8_t (rtc_to_bin)(uint8_t bcd_number);

#endif
