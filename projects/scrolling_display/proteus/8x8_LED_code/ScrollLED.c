/*
 * Use command:: gcc -D TESTING=1 file.c -I ./
 * 
 */

#include <string.h>
#include <lookup_table.h>

#if !(TESTING)
#include <REG51.H>

sbit Serial_Data = P1^1;
sbit SH_Clk = P1^0;
sbit ST_Clk = P1^2;
sbit CD4017_Clk = P1^3;
sbit CD4017_Rst = P1^4;
#else 
#include <stdio.h>
#endif

void delay_ms(unsigned int x)	 // delays x msec (at fosc=11.0592MHz)
{
    unsigned char j=0;
    while(x-- > 0)
    {
        for (j=0; j<125; j++){;}
    }
}

#if TESTING
void send_data(DISPLAY_WIDTH led_msg){
    unsigned char count = 0x00, ratio_count = 0x00;
    for (count = 0x00; count < LED_DISPLAY_BASE_WIDTH; count ++) {
        for (ratio_count = 0x00; ratio_count < LED_DISPLAY_RATIO_WIDTH; ratio_count ++) {
            if ((led_msg.width >> count) & 0x01) {
                printf ("1");
            }
            else {
                printf ("-");
            }
        }
    }
    printf ("\t");
}
#else
void send_data(DISPLAY_WIDTH temp){
    unsigned char t, Flag, ratio_count;
    for (t=0; t<LED_DISPLAY_BASE_WIDTH; t++){
        for (ratio_count = 0x00; ratio_count < LED_DISPLAY_RATIO_WIDTH; ratio_count ++) {
            Flag = ((temp.width >> t) & 0x01);
            if(Flag==0) Serial_Data = 0;
            else Serial_Data = 1;
            SH_Clk = 1;
            SH_Clk = 0;
        }
    }
    // Apply clock on ST_Clk
    ST_Clk = 1;
    ST_Clk = 0;  
}
#endif

DISPLAY_WIDTH DisplayBuffer [LED_DISPLAY_HIEGHT] [LED_DISPLAY_DIGITS] = {{0x00}};
unsigned int speed;
short  l, k, m, ShiftAmount, scroll, temp, shift_step=1, StringLength;
char message[]="ABCD123";
char index_data;
void main() {
    unsigned char select_line = 0x00, count, shift, ratio_count = 0x00;
    unsigned int backup;
    StringLength = strlen(message) ;
#if !(TESTING)
    do {
#endif
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
                                    DisplayBuffer [ShiftAmount][count - 1].width = DisplayBuffer [ShiftAmount][count - 1].width | (backup << (LED_DISPLAY_BASE_WIDTH - 1));
                                    for (ratio_count = 0x01; ratio_count < LED_DISPLAY_RATIO_HIEGHT; ratio_count ++) {
                                        DisplayBuffer [ShiftAmount + ratio_count][count - 1].width = DisplayBuffer [ShiftAmount][count - 1].width;
                                    }
                                }
                            }
                        }
                        backup = DisplayBuffer [ShiftAmount][count].width & 0x01;
                        DisplayBuffer [ShiftAmount][count - 1].width = DisplayBuffer [ShiftAmount][count - 1].width | (backup << (LED_DISPLAY_BASE_WIDTH - 1));
                        for (ratio_count = 0x01; ratio_count < LED_DISPLAY_RATIO_HIEGHT; ratio_count ++) {
                            DisplayBuffer [ShiftAmount + ratio_count][count - 1].width = DisplayBuffer [ShiftAmount][count - 1].width;
                        }
                    }
                    
                    DisplayBuffer [ShiftAmount][LED_DISPLAY_DIGITS - 1].width = (DisplayBuffer[ShiftAmount][LED_DISPLAY_DIGITS - 1].width >> shift_step) | (temp << ((LED_DISPLAY_BASE_WIDTH -1) - (scroll*shift_step)));
                    
                    for (ratio_count = 0x01; ratio_count < LED_DISPLAY_RATIO_HIEGHT; ratio_count ++) {
                        DisplayBuffer [ShiftAmount + ratio_count][LED_DISPLAY_DIGITS - 1].width = DisplayBuffer [ShiftAmount][LED_DISPLAY_DIGITS - 1].width;
                    }
                }
                
                speed = 1;
                
#if TESTING 
                for(l=0; l<speed;l++){
                    for (count=0; count<LED_DISPLAY_HIEGHT; count++) {
                        for (m = 0x00; m < LED_DISPLAY_DIGITS; m++) {
                            send_data(DisplayBuffer[count][m]);
                        }
                        printf ("\n");
                        delay_ms(1);
                    }
                    printf ("1234567812345678==============================================================================\n");
                } // l                
#else 
#if 0                
            for(l=0; l<speed;l++){
                for (count=0; count<LED_DISPLAY_HIEGHT; count++) {
                    for (m = 0x00; m < LED_DISPLAY_DIGITS; m++) {
                        send_data(DisplayBuffer[count][m]);
                    }
                    select_line = (0xFF & ~(0x01 << count));
                    P3 = select_line;
                    delay_ms(10);
                }
            }
#else                    
            for(l=0; l<speed;l++){
                for (count=0; count<LED_DISPLAY_HIEGHT; count++) {
                    for (m = 0x00; m < LED_DISPLAY_DIGITS; m++) {
                        send_data(DisplayBuffer[count][m]);
                        CD4017_Clk = 1;
                        CD4017_Clk = 0;
                        delay_ms(1);
                    }
                    CD4017_Rst = 1;
                    CD4017_Rst = 0;
                }
            }
#endif
#endif
            
            } // scroll
        } // k
        
#if !(TESTING)        
    } while(1);
#endif
}