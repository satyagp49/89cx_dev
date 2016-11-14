#include <REG51.H>
// LED Blink different rate with Switch press

sbit LED = P3^3;
sbit SW  = P3^2;

void delay_ms(unsigned int x);

void main()
{
	while(1)
	{
		if(SW == 0) // if switch is pressed
		{
			// Blink Fast
			LED = 0; // ON
			delay_ms(100);
			LED = 1; // OFF
			delay_ms(100);
		} else {
			// Blink Slow
			LED = 0; // ON
			delay_ms(1000);
			LED = 1; // OFF
			delay_ms(1000);
		}
	}	
}

void delay_ms(unsigned int x)	 // delays x msec (at fosc=11.0592MHz)
{
	unsigned char j=0;
	while(x-- > 0)
	{
		for (j=0; j<125; j++){;}
	}
}