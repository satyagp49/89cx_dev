#ifndef __arch_89cx_h__
#define __arch_89cx_h__

#include <datatypes.h>

#define LED_MESSAGE_LEN 48

#define LED_DIGIT_WIDTH     8
#define LED_DIGIT_HIGHT     8
#define LED_DISPLAY_NUMBER_OF_DIGITS 1

void controller_init_89cx (void);
void peripheral_init_89cx (void);

void timer_init_89cx (void);
void DelayMs_89cx (u16 ms);

void LedSendMessage_89cx (u8 led_msg);
void LedMoveToNextLine_89cx (void);
void LedResetLine_89cx (void);

#endif