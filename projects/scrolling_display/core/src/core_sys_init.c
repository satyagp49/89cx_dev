#include <stdio.h>
#include <led_message_scrolling.h>
#include <arch_xyz.h>
#include <string.h>

void timer_isr_testing (void);

void main (void) {
    u8 msg_str = 0x00;    
    controller_init ();
    
    peripheral_init ();

    //LedScrollInit ();
    
    //timer_isr_testing();
    
    //UpdateScrollMessage ("ABC");
    
    // timer delay testing
    /*while (1)
    {
        DelayMs (50);
        LED_INDICATION = 0x00;
        DelayMs (200);
        LED_INDICATION = 0x01;
    }*/             
    
    while (1)
    {
        msg_str = uart_get_char ();
		if ((msg_str != 0) && (msg_str != 0xFF)) {
			printf ("%c\r", msg_str);
		}
    }
    printf ("\n");
}

void toggle_led (void) {
    if (LED_INDICATION == 0) {
        LED_INDICATION = 1;
    }
    else {
        LED_INDICATION = 0;
    }
}
void timer_isr_testing () {
    TIMER_CONFIG timer_config;
    LED_INDICATION = 0;
    timer_config.timer = TIMER_0;
    timer_config.time_out = 50;
    timer_config.isr_handler = toggle_led;
    timer_init (&timer_config);
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