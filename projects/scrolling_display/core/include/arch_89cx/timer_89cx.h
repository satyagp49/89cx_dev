#ifndef __timer_89cx_h__
#define __timer_89cx_h__

#include <datatypes.h>

typedef enum timer_number {
    TIMER_0,
    TIMER_1,

    TIMER_MAX,
}TIMER_NUMBER;

typedef struct timer_config {
    TIMER_NUMBER timer;
    uint time_out;
    void (*isr_handler)(void);
}TIMER_CONFIG;

void timer_init_89cx (TIMER_CONFIG *timer_config);
void DelayMs_89cx (u16 ms);

#endif
