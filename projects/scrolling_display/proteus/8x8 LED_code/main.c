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

void display_data (unsigned char data_send) {
    unsigned char count = 0x00;
    unsigned char flag = 0x00; 
    for (count = 0x00; count < 8; count ++) {
        flag = ((data_send >> count) & 0x01);
        if (flag == 0x00) {
            DS = 0;
        }
        else {
            DS = 1;
        }
        SH_CP = 1;    
        SH_CP = 0;    
    }
    // Apply clock on ST_CP
    ST_CP = 1;    
    ST_CP = 0;                            
}
void main()
{
    unsigned char count = 0x00;
    unsigned char ascii_data [] = {0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11};
	while(1)
	{
        for (count = 0x00; count < 8; count ++) {		
            display_data (ascii_data [count]);
            //delay_ms(10);
        }
	}	
}