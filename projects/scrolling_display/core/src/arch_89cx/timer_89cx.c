
#include <arch_89cx.h>

void (*timer0_isr_callback)();
uint Timer0Timeout = 0x00;

void timer_init_89cx (TIMER_CONFIG *timer_config) {
    switch (timer_config-> timer) {
        case TIMER_0: {	
            EA = 0; /* disable interrupts */
        	TR0 = 0; /* stop timer 0 */
        	TMOD &= ~0x0F; /* clear timer 0 mode bits */
        	TMOD |= 0x01; /* put timer 0 into 16-bit no prescale */
            Timer0Timeout = timer_config-> time_out;
        	TL0 = 0x18;
        	TH0 = 0xFC;
        	PT0 = 0; /* set low priority for timer 0 */
        	ET0 = 1; /* enable timer 0 interrupt */
        	TR0 = 1; /* start timer 0 */
        	EA = 1; /* enable interrupts */
        	timer0_isr_callback = timer_config-> isr_handler;
        }
        break;
        case TIMER_1: {
        }
        break;
        default: {
        }
        break;
    }
}	  

void timer0_isr (void) interrupt 1
{
    static uint timer0timeout = 0x00;
    TR0 = 0; /* stop timer 0 */
	TL0 = 0x18;
	TH0 = 0xFC;

    timer0timeout++;
    if (Timer0Timeout <= timer0timeout) 
    {
        timer0_isr_callback ();
        timer0timeout = 0x00;
    }

    TR0 = 1; /* start timer 0 for next cycle s*/
}

void DelayMs_89cx (u16 ms) { // delays x msec (at fosc=11.0592MHz)
    u16 count=0;
    while(count < ms) {
        CTR2 = 0;	//16-bit timer2 selected
        TH2=0xFC;	// 0XFC18 for 1ms Loading high byte in TH
        TL2=0x18;	// Loaded low byte in TL
        TR2=1;		// Running the timer
        while (!TF2);   //Checking the timer flag register if it is not equal to 1 
        TR2 = 0;	  // If TF1=1 stop the timer
        TF2 = 0;	  // Clear the Timer Flag bit for next calculation
        count++;
    }
}