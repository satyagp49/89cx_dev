

#include <stdio.h>
#include <led_message_scrolling.h>
#include <arch_xyz.h>

u32 count = 0x00;
void toggle_led (void) {
    if (count == 100) {
        count = 0x00;
        if (LED == 0) {
            LED = 1;
        }
        else {
            LED = 0;
        }
    }
    count ++;
}

void main (void) {
    
    TIMER_CONFIG timer_config;
    
    controller_init ();
    
    peripheral_init ();
    LED = 0;
    timer_config.timer = TIMER_0;
    timer_config.time_out = 10;
    timer_config.isr_handler = toggle_led;
    timer_init (&timer_config);

    //LedScrollInit ();
    
    
    //UpdateScrollMessage ("ABC");
    while (1);
    
    printf ("\n");
}


#if 0

01110000
10001000
10001000
10001000
11111000
10001000
10001000
10001000

01111000
10001000
10001000
01111000
10001000
10001000
10001000
01111000

#endif