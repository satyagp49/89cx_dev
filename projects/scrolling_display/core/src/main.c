

#include <stdio.h>
#include <led_message_scrolling.h>
#include <arch_89cx.h>

int main (void) {
    
    controller_init ();
    
    peripheral_init ();
    
    timer_init ();
    
    ScrollMessage ("ABCDEF");
    
    printf ("\n");
    return 0;
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