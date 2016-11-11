

#include <stdio.h>
#include <led_message_scrolling.h>
#include <arch_89cx.h>

int main (void) {
    
    controller_init ();
    
    peripheral_init ();
    
    timer_init ();
    
    ScrollMessage ("A");
    
    printf ("\n");
    return 0;
}