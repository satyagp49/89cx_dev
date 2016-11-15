#ifndef __arch_89cx_h__
#define __arch_89cx_h__

#include <datatypes.h>
#include <timer_89cx.h>
#include <uart_89cx.h>
#include <REG51_89EV516RD.H>

sbit LED_INDICATION = P3^3;

#define LED_MESSAGE_LEN 48

#define LED_DIGIT_WIDTH     8
#define LED_DIGIT_HIGHT     8
#define LED_DISPLAY_NUMBER_OF_DIGITS 1

void controller_init_89cx (void);
void peripheral_init_89cx (void);
u16 uart_get_str (u8 *msg_str, u16 len);
u8 uart_get_char (void);

void LedSendMessage_89cx (u8 led_msg);
void LedMoveToNextLine_89cx (void);
void LedResetLine_89cx (void);

#endif