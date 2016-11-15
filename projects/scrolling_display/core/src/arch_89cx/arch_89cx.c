#include <arch_89cx.h>
void controller_init_89cx (void) {
    
}

void peripheral_init_89cx (void) {
    UartInit ();
}

    
void LedSendMessage_89cx (u8 led_msg) {
    u8 count = 0x00;
    
    for (count = 0x00; count < LED_DIGIT_WIDTH; count ++) {
        printf ("%x", (led_msg >> count) & 0x01);
    }
    printf ("\t");
}

void LedMoveToNextLine_89cx (void) {
    printf (">>>>\n");
}

void LedResetLine_89cx (void) {
    printf ("----------\n");
}