
#include <led_message_scrolling.h>
#include <string.h>
#include <arch_xyz.h>

static const u16 ASCII_Lookup_8x8[][8] ={
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000000, 0b00000100},
    {0b00001010, 0b00001010, 0b00001010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b00001010, 0b00011111, 0b00001010, 0b00011111, 0b00001010, 0b00011111, 0b00001010},
    {0b00000111, 0b00001100, 0b00010100, 0b00001100, 0b00000110, 0b00000101, 0b00000110, 0b00011100},
    {0b00011001, 0b00011010, 0b00000010, 0b00000100, 0b00000100, 0b00001000, 0b00001011, 0b00010011},
    {0b00000110, 0b00001010, 0b00010010, 0b00010100, 0b00001001, 0b00010110, 0b00010110, 0b00001001},
    {0b00000100, 0b00000100, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b00000010, 0b00000100, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010},
    {0b00001000, 0b00000100, 0b00000010, 0b00000010, 0b00000010, 0b00000010, 0b00000100, 0b00001000},
    {0b00010101, 0b00001110, 0b00011111, 0b00001110, 0b00010101, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b00011111, 0b00000100, 0b00000100, 0b00000000},
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000110, 0b00000100, 0b00001000},
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100},
    {0b00000001, 0b00000010, 0b00000010, 0b00000100, 0b00000100, 0b00001000, 0b00001000, 0b00010000},
    {0b00001110, 0b00010001, 0b00010011, 0b00010001, 0b00010101, 0b00010001, 0b00011001, 0b00001110},
    {0b00000100, 0b00001100, 0b00010100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00011111},
    {0b00001110, 0b00010001, 0b00010001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00011111},
    {0b00001110, 0b00010001, 0b00000001, 0b00001110, 0b00000001, 0b00000001, 0b00010001, 0b00001110},
    {0b00010000, 0b00010000, 0b00010100, 0b00010100, 0b00011111, 0b00000100, 0b00000100, 0b00000100},
    {0b00011111, 0b00010000, 0b00010000, 0b00011110, 0b00000001, 0b00000001, 0b00000001, 0b00011110},
    {0b00000111, 0b00001000, 0b00010000, 0b00011110, 0b00010001, 0b00010001, 0b00010001, 0b00001110},
    {0b00011111, 0b00000001, 0b00000001, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000},
    {0b00001110, 0b00010001, 0b00010001, 0b00001110, 0b00010001, 0b00010001, 0b00010001, 0b00001110},
    {0b00001110, 0b00010001, 0b00010001, 0b00001111, 0b00000001, 0b00000001, 0b00000001, 0b00000001},
    {0b00000000, 0b00000100, 0b00000100, 0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b00000000},
    {0b00000000, 0b00000100, 0b00000100, 0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b00001000},
    {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000001},
    {0b00000000, 0b00000000, 0b00000000, 0b00011110, 0b00000000, 0b00011110, 0b00000000, 0b00000000},
    {0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000010, 0b00000100, 0b00001000, 0b00010000},
    {0b00001110, 0b00010001, 0b00010001, 0b00000010, 0b00000100, 0b00000100, 0b00000000, 0b00000100},
    {0b00001110, 0b00010001, 0b00010001, 0b00010101, 0b00010101, 0b00010001, 0b00010001, 0b00011110},
    {0b00001110, 0b00010001, 0b00010001, 0b00010001, 0b00011111, 0b00010001, 0b00010001, 0b00010001},   // A    
    {0b00011110, 0b00010001, 0b00010001, 0b00011110, 0b00010001, 0b00010001, 0b00010001, 0b00011110},
    {0b00000111, 0b00001000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00001000, 0b00000111},
    {0b00011100, 0b00010010, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010010, 0b00011100},
    {0b00011111, 0b00010000, 0b00010000, 0b00011110, 0b00010000, 0b00010000, 0b00010000, 0b00011111},
    {0b00011111, 0b00010000, 0b00010000, 0b00011110, 0b00010000, 0b00010000, 0b00010000, 0b00010000},
    {0b00001110, 0b00010001, 0b00010000, 0b00010000, 0b00010111, 0b00010001, 0b00010001, 0b00001110},
    {0b00010001, 0b00010001, 0b00010001, 0b00011111, 0b00010001, 0b00010001, 0b00010001, 0b00010001},
    {0b00011111, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00011111},
    {0b00011111, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00010100, 0b00001000},
    {0b00010001, 0b00010010, 0b00010100, 0b00011000, 0b00010100, 0b00010010, 0b00010001, 0b00010001},
    {0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00011111},
    {0b00010001, 0b00011011, 0b00011111, 0b00010101, 0b00010001, 0b00010001, 0b00010001, 0b00010001},
    {0b00010001, 0b00011001, 0b00011001, 0b00010101, 0b00010101, 0b00010011, 0b00010011, 0b00010001},
    {0b00001110, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00001110},
    {0b00011110, 0b00010001, 0b00010001, 0b00011110, 0b00010000, 0b00010000, 0b00010000, 0b00010000},
    {0b00001110, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010101, 0b00010011, 0b00001111},
    {0b00011110, 0b00010001, 0b00010001, 0b00011110, 0b00010100, 0b00010010, 0b00010001, 0b00010001},
    {0b00001110, 0b00010001, 0b00010000, 0b00001000, 0b00000110, 0b00000001, 0b00010001, 0b00001110},
    {0b00011111, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100},
    {0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00001110},
    {0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00001010, 0b00000100},
    {0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010101, 0b00010101, 0b00001010},
    {0b00010001, 0b00010001, 0b00001010, 0b00000100, 0b00000100, 0b00001010, 0b00010001, 0b00010001},
    {0b00010001, 0b00010001, 0b00001010, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100},
    {0b00011111, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00010000, 0b00011111},
    {0b00001110, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001110},
    {0b00010000, 0b00001000, 0b00001000, 0b00000100, 0b00000100, 0b00000010, 0b00000010, 0b00000001},
    {0b00001110, 0b00000010, 0b00000010, 0b00000010, 0b00000010, 0b00000010, 0b00000010, 0b00001110},
    {0b00000100, 0b00001010, 0b00010001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011111},
    {0b00001000, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00010010, 0b00010010, 0b00010010, 0b00001111},
    {0b00000000, 0b00010000, 0b00010000, 0b00010000, 0b00011100, 0b00010010, 0b00010010, 0b00011100},
    {0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00010000, 0b00010000, 0b00010000, 0b00001110},
    {0b00000000, 0b00000001, 0b00000001, 0b00000001, 0b00000111, 0b00001001, 0b00001001, 0b00000111},
    {0b00000000, 0b00000000, 0b00000000, 0b00011100, 0b00010010, 0b00011110, 0b00010000, 0b00001110},
    {0b00000000, 0b00000011, 0b00000100, 0b00000100, 0b00000110, 0b00000100, 0b00000100, 0b00000100},
    {0b00000000, 0b00001110, 0b00001010, 0b00001010, 0b00001110, 0b00000010, 0b00000010, 0b00001100},
    {0b00000000, 0b00010000, 0b00010000, 0b00010000, 0b00011100, 0b00010010, 0b00010010, 0b00010010},
    {0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00000100, 0b00000100, 0b00000100, 0b00000100},
    {0b00000000, 0b00000010, 0b00000000, 0b00000010, 0b00000010, 0b00000010, 0b00000010, 0b00001100},
    {0b00000000, 0b00010000, 0b00010000, 0b00010100, 0b00011000, 0b00011000, 0b00010100, 0b00010000},
    {0b00000000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00001100},
    {0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00010101, 0b00010001, 0b00010001, 0b00010001},
    {0b00000000, 0b00000000, 0b00000000, 0b00010100, 0b00011010, 0b00010010, 0b00010010, 0b00010010},
    {0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00010010, 0b00010010, 0b00010010, 0b00001100},
    {0b00000000, 0b00011100, 0b00010010, 0b00010010, 0b00011100, 0b00010000, 0b00010000, 0b00010000},
    {0b00000000, 0b00001110, 0b00010010, 0b00010010, 0b00001110, 0b00000010, 0b00000010, 0b00000001},
    {0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00001100, 0b00001000, 0b00001000, 0b00001000},
    {0b00000000, 0b00000000, 0b00001110, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00011110},
    {0b00000000, 0b00010000, 0b00010000, 0b00011100, 0b00010000, 0b00010000, 0b00010000, 0b00001100},
    {0b00000000, 0b00000000, 0b00000000, 0b00010010, 0b00010010, 0b00010010, 0b00010010, 0b00001100},
    {0b00000000, 0b00000000, 0b00000000, 0b00010001, 0b00010001, 0b00010001, 0b00001010, 0b00000100},
    {0b00000000, 0b00000000, 0b00000000, 0b00010001, 0b00010001, 0b00010001, 0b00010101, 0b00001010},
    {0b00000000, 0b00000000, 0b00000000, 0b00010001, 0b00001010, 0b00000100, 0b00001010, 0b00010001},
    {0b00000000, 0b00000000, 0b00010001, 0b00001010, 0b00000100, 0b00001000, 0b00001000, 0b00010000},
    {0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00000010, 0b00000100, 0b00001000, 0b00011111},
    {0b00000010, 0b00000100, 0b00000100, 0b00000100, 0b00001000, 0b00000100, 0b00000100, 0b00000010},
    {0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100},
    {0b00001000, 0b00000100, 0b00000100, 0b00000100, 0b00000010, 0b00000100, 0b00000100, 0b00001000},
    {0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00011110, 0b00010100, 0b00000000, 0b00000000}
};

static s8 ScrollMessage [LED_MESSAGE_LEN] = {0};

void UpdateScrollMessage (s8 *message) {
    if (strlen (message) > LED_MESSAGE_LEN) {
        return ;
    }
    
    strncpy(ScrollMessage, message, strlen (message));
}

static void ThreadScrollMessage (void) {
    u8 digit_count = 0x00;
    u8 number_of_segments = 0x00;
    s8 segment_iteration = 0x00;
    u8 offset = 0x00;
    u8 msg_len = 0x00;
    u8 msg_count = 0x00;
    u8 digit_hight = 0x00;
    u16 store_lookup = 0x00;
    
    msg_len = strlen(ScrollMessage);

    if ((LED_DISPLAY_NUMBER_OF_DIGITS / msg_len) > 0x00) {
        for (digit_hight = 0x00; digit_hight < LED_DIGIT_HIGHT; digit_hight ++) {
            for (msg_count = 0x00; msg_count < msg_len; msg_count ++) {            
                store_lookup = ASCII_Lookup_8x8[(ScrollMessage [msg_count] - 32)][digit_hight];                
                LedSendMessage (store_lookup);
            }
            LedMoveToNextLine ();
        }
        LedResetLine ();
    }
    else {
        number_of_segments = (LED_DISPLAY_NUMBER_OF_DIGITS % msg_len);
        segment_iteration = (msg_len / LED_DISPLAY_NUMBER_OF_DIGITS);

        for (; (segment_iteration > -1) && (offset < msg_len); segment_iteration --, offset += number_of_segments) {
            for (digit_hight = 0x00; (digit_hight < LED_DIGIT_HIGHT); digit_hight ++) {
                for (msg_count = offset, digit_count = 0x00; (digit_count < number_of_segments) && (msg_count < msg_len); digit_count ++, msg_count ++) {            
                    store_lookup = ASCII_Lookup_8x8[(ScrollMessage [msg_count] - 32)][digit_hight];                
                    LedSendMessage (store_lookup);
                }
                LedMoveToNextLine ();
            }
            LedResetLine ();
            DelayMs (100);
        }
    }
}
