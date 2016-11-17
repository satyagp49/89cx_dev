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
 
void send_data(unsigned int temp){
 unsigned int Mask = 0x0001, t, Flag;
  for (t=0; t<16; t++){
   Flag = temp & Mask;
   if(Flag==0) Serial_Data = 0;
   else Serial_Data = 1;
   SH_Clk = 1;
   SH_Clk = 0;
   Mask = Mask << 1;
  }
  // Apply clock on ST_Clk
  ST_Clk = 1;
  ST_Clk = 0;

}

unsigned int DisplayBuffer[]={0,0,0,0,0,0,0,0};
unsigned int speed;
short  l, k, ShiftAmount, scroll, temp, shift_step=1, StringLength;
char message[]="AB";
char index;
void main() {
    unsigned char select_line = 0x00, count;
    StringLength = strlen(message) ;
    do {
        for (k=0; k<StringLength; k++){
			for (scroll=0; scroll<(8/shift_step); scroll++) {
				for (ShiftAmount=0; ShiftAmount<8; ShiftAmount++){
					index = message[k];
					temp = CharData[index-32][ShiftAmount];
					DisplayBuffer[ShiftAmount] = (DisplayBuffer[ShiftAmount] << shift_step)| (temp >> ((8-shift_step)-scroll*shift_step));
				}
				
				speed = 1;
				for(l=0; l<speed;l++){
					for (count=0; count<8; count++) {
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