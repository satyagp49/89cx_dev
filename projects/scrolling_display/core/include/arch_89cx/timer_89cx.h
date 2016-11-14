
#include <datatypes.h>

#define TIMER0_COUNT 0xFF00 /* 10000h - ((11,059,200 Hz / (12 * FREQ)) - 17) */

void timer_init_89cx (void (*isr_handler)());
void DelayMs_89cx (u16 ms);
