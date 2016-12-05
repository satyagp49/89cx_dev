#include <REG51.H>
#include <string.h>
#include <lookup_table.h>

 sbit Serial_Data = P0^1;
 sbit SH_Clk = P0^0;
 sbit ST_Clk = P0^2;

void delay_ms(unsigned int x)	 // delays x msec (at fosc=11.0592MHz)
{
	unsigned char j=0;
	while(x-- > 0)
	{
		for (j=0; j<125; j++){;}
	}
}
 
void send_data(LED_MEM_REPLICA temp){
 unsigned int t, Flag;
  for (t=0; t<LED_DISPLAY_ROW_SIZE; t++){
   Flag = ((temp.row >> t) & 0x01);
   if(Flag==0) Serial_Data = 0;
   else Serial_Data = 1;
   SH_Clk = 1;
   SH_Clk = 0;
  }
  // Apply clock on ST_Clk
  ST_Clk = 1;
  ST_Clk = 0;  
}

unsigned short int DisplayBuffer [LED_DISPLAY_DIGITS][LED_DISPLAY_HIEGHT] = {{0x00}};
unsigned int speed;
short  l, k, m, ShiftAmount, scroll, temp, shift_step=1, StringLength;
char message[]="ABCD123";
char index;
void main() {
    unsigned char select_line = 0x00, count;
    StringLength = strlen(message) ;
    do {
        for (k=0; k<StringLength; k++){
			for (scroll=0; scroll<(LED_DISPLAY_WIDTH/shift_step); scroll++) {
				for (ShiftAmount=0; ShiftAmount<LED_DISPLAY_HIEGHT; ShiftAmount++){
					index = message[k];
                    for (l = 0x00; l < LED_DISPLAY_DIGITS; l ++) {
                        for (m = 0x00; m < LED_DISPLAY_HIEGHT; m ++) {
                            DisplayBuffer [l][m] >>= 
                        }                                   
                    }
					temp = CharData[index][ShiftAmount];
                    DisplayBuffer[ShiftAmount] = (DisplayBuffer[ShiftAmount] >> shift_step) | (temp << ((LED_DISPLAY_ROW_SIZE -1) - (scroll*shift_step)));
					//DisplayBuffer[ShiftAmount] = (DisplayBuffer[ShiftAmount] << shift_step) | (temp >> ((8-shift_step)-scroll*shift_step));
				}
				speed = 1;
				for(l=0; l<speed;l++){
					for (count=0; count<LED_DISPLAY_HIEGHT; count++) {
						send_data(DisplayBuffer[count]);
						select_line = (0xFF & ~(0x01 << count));
						P3 = select_line;
						delay_ms(10);
					}  // i
				} // l
			} // scroll
		} // k
	} while(1);
}