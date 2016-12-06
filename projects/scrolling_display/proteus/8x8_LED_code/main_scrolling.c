/*
  Project: Scrolling message on LED dot matrix display
  MCU: PIC18F2550 @ 48.0 MHz (StartUSB for PIC board)
  Copyright @ Rajendra Bhatt
  May 16, 2011
*/

// Define LCD module connections.
/* sbit Serial_Data at LATC2_bit;
 sbit SH_Clk at LATC6_bit;
 sbit ST_Clk at LATC7_bit;
 sbit CD4017_Clk at LATA2_bit;
 sbit CD4017_RST at LATA1_bit;
  */

 #include <REG51.H>
 #include <string.h>
 sbit Serial_Data = P1^1;
 sbit SH_Clk  = P1^0;
 sbit ST_Clk  = P1^2;
 sbit CD4017_Clk  = P1^3;
 sbit CD4017_Rst  = P1^4;

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

void Delay_ms(unsigned int x)	 // delays x msec (at fosc=11.0592MHz)
{
    unsigned char j=0;
    while(x-- > 0)
    {
        for (j=0; j<125; j++){;}
    }
}
/* CharData is a two dimensional constant array that holds the 8-bit column values of
   individual rows for ASCII characters that are to be displayed on a 8x8 matrix format.
*/
const unsigned short CharData[][8] ={{0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}};

unsigned int DisplayBuffer[]={0,0,0,0,0,0,0,0};
unsigned int speed;
short i, l, k, ShiftAmount, scroll, temp, shift_step=1, StringLength;
char message[]="A";
char index;
void main() {
 StringLength = strlen(message) ;
 do {
 for (k=0; k<StringLength; k++){
  for (scroll=0; scroll<(8/shift_step); scroll++) {
   for (ShiftAmount=0; ShiftAmount<8; ShiftAmount++){
    index = message[k];
    temp = CharData[index-65][ShiftAmount];
    DisplayBuffer[ShiftAmount] = (DisplayBuffer[ShiftAmount] << shift_step)| (temp >> ((8-shift_step)-scroll*shift_step));
   }

  speed = 1;
  for(l=0; l<speed;l++){

   for (i=0; i<8; i++) {

    send_data(DisplayBuffer[i]);
    CD4017_Clk = 1;
    CD4017_Clk = 0;
    Delay_ms(1);
   }  // i
  CD4017_Rst = 1;
  CD4017_Rst = 0;
  } // l
  } // scroll
 } // k

 } while(1);

}