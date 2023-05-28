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


///@brief Set up the RTC.
///@note This function sets up the RTC by updating the time information and determining the RTC mode.
void (rtc_setup)();

///@brief Subscribe to RTC interrupts.
///@note This function subscribes to RTC interrupts by setting the appropriate bit in the bit_no and calling sys_irqsetpolicy to register the interrupt handler.
///@param bit Pointer to the bit number that will hold the RTC interrupt bit.
///@return 0 if the subscription is successful, otherwise returns 1.
int (rtc_subscribe_int)(uint8_t *bit);

///@brief Unsubscribe from RTC interrupts.
///@note This function unsubscribes from RTC interrupts by removing the previously set interrupt policy using sys_irqrmpolicy.
///@return 0 if the unsubscription is successful, otherwise returns 1.
int (rtc_unsubscribe_int)();

///@brief Output a command to the RTC.
///@note This function outputs a command to the RTC by writing to the appropriate register and retrieves the output from the RTC.
///@param command The command to be sent to the RTC.
///@param output Pointer to store the output received from the RTC.
///@return 0 if the output is successful, otherwise returns 1.
int (rtc_output)(uint8_t command, uint8_t *output);


///@brief Check if RTC is busy.
///@note This function checks if the RTC is busy updating its internal registers.
///@return 1 if RTC is busy, 0 otherwise.
int (rtc_busy)();


///@brief Check if RTC is in binary mode.
///@note This function checks if the RTC is in binary mode.
///@return 1 if RTC is in binary mode, 0 otherwise.
int (rtc_check_binary)();


///@brief Check if RTC is in BCD mode.
///@note This function checks if the RTC is in BCD mode.
///@return 1 if RTC is in BCD mode, 0 otherwise.
int (rtc_check_bcd)();

///@brief Update the RTC time information.
///@note This function updates the time information by reading the appropriate RTC registers and storingthe information in the time_info structure.
///@return 0 if the update is successful, otherwise returns 1.
int (rtc_update_time)();

///@brief Convert BCD number to binary.
///@note This function converts a BCD number to binary format.
///@param number The BCD number to be converted.
///@return The converted binary number.
uint8_t (rtc_to_bin)(uint8_t bcd_number);

#endif
