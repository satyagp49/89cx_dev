#include <REG51.H>

//LED Blink

sbit DS = P0^1;
sbit SH_CP = P0^0;
sbit ST_CP = P0^2;

sbit NEXT_LINE = P3^0;
sbit RESET_LINE = P3^1;


void delay_ms(unsigned int x)	 // delays x msec (at fosc=11.0592MHz)
{
	unsigned char j=0;
	while(x-- > 0)
	{
		for (j=0; j<125; j++){;}
	}
}
void display_data(unsigned char temp){
 unsigned char Mask = 0x01, t, Flag;
  for (t=0; t<8; t++){
   Flag = temp & Mask;
   if(Flag==0) DS = 0;
   else DS = 1;
   SH_CP = 1;
   delay_ms(100);
   SH_CP = 0;
   Mask = Mask << 1;

  }
  // Apply clock on ST_Clk
  ST_CP = 1;
  delay_ms(100);
  ST_CP = 0;

}
void main()
{   
    unsigned char count = 0x00, count1 = 0x00, flag = 0x00;
     //test counter
    /*RESET_LINE = 1;
    RESET_LINE = 0;
    while (1) {
        NEXT_LINE = 1;
        NEXT_LINE = 0;               
        delay_ms(100);                   
    }*/

    unsigned char ascii_data [] = {0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11};
	while(1)
	{
        for (count = 0x00; count < 8; count ++) {		
            display_data (ascii_data [count]);
            delay_ms(10);
        }
	} 
    /*
    while (1) {
        ST_CP = 1;
        delay_ms(100);
        ST_CP = 0;    
        delay_ms(100);           
    } */
    /*
    while (1) {
        for (count1 = 0x00; count1 < 8; count1 ++) {
            for (count = 0x00; count < 8; count ++) {		
                if (flag == 0x00) {
                    DS = 0;
                    flag = 1; 
                }
                else {
                    DS = 1;
                    flag = 0x00;
                }
                SH_CP = 1;    
                SH_CP = 0;    
            }
        ST_CP = 1;    
        ST_CP = 0;  
        delay_ms(100);                   
        }
        RESET_LINE = 1;        
        RESET_LINE = 0;
    }*/	


}