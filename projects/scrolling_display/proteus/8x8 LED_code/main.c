#include <REG51.H>

//LED Blink

sbit DS = P0^1;
sbit SH_CP = P0^0;
sbit ST_CP = P0^2;


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
   SH_CP = 0;
   Mask = Mask << 1;
  }
  // Apply clock on ST_Clk
  ST_CP = 1;
  ST_CP = 0;
  //delay_ms(200);
}
void main()
{   
    unsigned char count = 0x00, select_line = 0x00;
    unsigned char ascii_data [] = {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00};

	while(1)
	{
        for (count = 0x00; count < 8; count ++) {		
            display_data (ascii_data [count]);
            select_line = (0xFF & ~(0x01 << count));
            P3 = select_line;
            delay_ms(10);
        }

	} 
     //test counter
    /*RESET_LINE = 1;
    RESET_LINE = 0;
    while (1) {
        NEXT_LINE = 1;
        NEXT_LINE = 0;               
        delay_ms(100);                   
    }*/

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