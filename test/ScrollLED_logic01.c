#include <stdio.h>
#include <string.h>
#include "lookup_table.h"

void delay_ms(unsigned int x)	 // delays x msec (at fosc=11.0592MHz)
{
	unsigned char j=0;
	while(x-- > 0)
	{
		for (j=0; j<125; j++){;}
	}
}

 void send_data(DISPLAY_WIDTH led_msg){
    int count = 0x00;
    unsigned char ratio_count = 0x00;
    for (count = 0x00; count < LED_DISPLAY_WIDTH; count ++) {
        for (ratio_count = 0x00; ratio_count < LED_DISPLAY_RATIO_WIDTH; ratio_count ++) {
            if ((led_msg.width >> count) & 0x01) {
                printf ("1");
            }
            else
                printf ("-");
        }        
    }
    printf ("\t");
}

DISPLAY_WIDTH DisplayBuffer [LED_DISPLAY_HIEGHT] [LED_MAX_DISPLAY_DIGITS] = {{0x00}};
unsigned int speed;
short  l, k, m, ShiftAmount, scroll, temp, shift_step=1, StringLength;
char message[]="AB";
short index_data;
int main() {
    unsigned char count, shift, ratio_count = 0x00;
    unsigned int backup;
    StringLength = strlen(message) ;
    //do {
        for (k=0; k<StringLength; k++){
            for (scroll=0; scroll<(LED_DISPLAY_BASE_WIDTH/shift_step); scroll++) {
                for (ShiftAmount=0; ShiftAmount < (LED_DISPLAY_BASE_HIEGHT * LED_DISPLAY_RATIO_HIEGHT); ShiftAmount += LED_DISPLAY_RATIO_HIEGHT){
                    index_data = message[k];
                    temp = CharData[index_data][(ShiftAmount/LED_DISPLAY_RATIO_HIEGHT)];
                    if (LED_DISPLAY_DIGITS > 1) {
                        for (shift = 0x00; shift<shift_step;shift++) {
                            for (count = 0; count < (LED_DISPLAY_DIGITS - 1);count ++) {
                                if (count == 0x00) {
                                    DisplayBuffer [ShiftAmount][count].width >>= 1;
                                }
                                else {
                                    backup = DisplayBuffer [ShiftAmount][count].width & 0x01;
                                    DisplayBuffer [ShiftAmount][count].width >>= 1;
                                    DisplayBuffer [ShiftAmount][count - 1].width = DisplayBuffer [ShiftAmount][count - 1].width | (backup << 7);
                                    for (ratio_count = 0x00; ratio_count < LED_DISPLAY_RATIO_HIEGHT; ratio_count ++) {
                                        DisplayBuffer [ShiftAmount + ratio_count][count - 1].width = DisplayBuffer [ShiftAmount][LED_DISPLAY_DIGITS - 1].width;
                                    }
                                }
                            }
                        }
                        backup = DisplayBuffer [ShiftAmount][count].width & 0x01;
                        DisplayBuffer [ShiftAmount][count - 1].width = DisplayBuffer [ShiftAmount][count - 1].width | (backup << 7);
                        for (ratio_count = 0x00; ratio_count < LED_DISPLAY_RATIO_HIEGHT; ratio_count ++) {
                            DisplayBuffer [ShiftAmount + ratio_count][count - 1].width = DisplayBuffer [ShiftAmount][LED_DISPLAY_DIGITS - 1].width;
                        }
                    }
                    
                    DisplayBuffer [ShiftAmount][LED_DISPLAY_DIGITS - 1].width = (DisplayBuffer[ShiftAmount][LED_DISPLAY_DIGITS - 1].width >> shift_step) | (temp << ((LED_DISPLAY_BASE_WIDTH -1) - (scroll*shift_step)));
                    
                    for (ratio_count = 0x00; ratio_count < LED_DISPLAY_RATIO_HIEGHT; ratio_count ++) {
                        DisplayBuffer [ShiftAmount + ratio_count][LED_DISPLAY_DIGITS - 1].width = DisplayBuffer [ShiftAmount][LED_DISPLAY_DIGITS - 1].width;
                    }
               }

                speed = 1;
                for(l=0; l<speed;l++){
                    for (count=0; count<LED_DISPLAY_HIEGHT; count++) {
                        for (m = 0x00; m < LED_DISPLAY_DIGITS; m++) {
                            send_data(DisplayBuffer[count][m]);
                        }
                        printf ("\n");
                        delay_ms(1);
                    }
                    printf ("==============================================================================\n");
                } // l
            } // scroll
        } // k
    //} while(1);

    return 0;
}
