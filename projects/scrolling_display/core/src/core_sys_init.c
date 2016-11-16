#include <stdio.h>
#include <string.h>

#include <arch_xyz.h>
#include <command_mode.h>
#include <led_message_scrolling.h>

void main (void) {
     
    controller_init ();
    
    peripheral_init ();

    LedScrollInit ();
        
    while (1) {
        CommandMode ();
    }
}

#if 0
void timer_testing (void) {
    // timer delay testing
    while (1)
    {
        DelayMs (50);
        LED_INDICATION = 0x00;
        DelayMs (200);
        LED_INDICATION = 0x01;
    }             
}
void uart_testing (void) {
#define MSG_LEN     30
    u8 msg_buff [MSG_LEN] = {0x00};

    //uart testing
    while (1) {
        if (UartGetStr (msg_buff, MSG_LEN) > 0) {
            printf ("%s", msg_buff);
            memset (msg_buff, 0x00, MSG_LEN);
        }
    }
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
#endif

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