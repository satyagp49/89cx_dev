#ifndef __scroll_data_h__
#define __scroll_data_h__

#include <datatypes.h>

#define LED_DIGIT_WIDTH     8
#define LED_DIGIT_HIGHT     8
#define LED_NUMBER_OF_DIGITS 1
#define LED_ROW_SIZE (LED_NUMBER_OF_DIGITS * LED_DIGIT_WIDTH)

typedef struct {
    unsigned row: LED_ROW_SIZE;
}LED_DISPLAY_BUFFER;

void ScrollMessage (s8 *message);

#endif