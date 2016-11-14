
#include <arch_89cx.h>
#include <REG51.H>

void (*timer0_isr_callback)();

void timer_init_89cx (TIMER_CONFIG *timer_config) {

    switch (timer_config-> timer) {
        case TIMER_0: {	
            EA = 0; /* disable interrupts */
        	TR0 = 0; /* stop timer 0 */
        	TMOD &= ~0x0F; /* clear timer 0 mode bits */
        	TMOD |= 0x01; /* put timer 0 into 16-bit no prescale */
        	TL0 = (TIMER0_COUNT & 0x00FF);
        	TH0 = (TIMER0_COUNT >> 8);
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
    uint itmp;
    /*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    Stop Timer 0, adjust the timer 0 counter so that
    we get another interrupt in 10ms, and restart the
    timer.
    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    TR0 = 0; /* stop timer 0 */
    itmp = TIMER0_COUNT + TL0 + (TH0<<8);
    TL0 = itmp;
    TH0 = itmp >> 8;
    
    timer0_isr_callback ();
    
    TR0 = 1; /* start timer 0 for next cycle s*/
}

void DelayMs_89cx (unsigned int x) { // delays x msec (at fosc=11.0592MHz)
    u8 j=0;
	while (x-- > 0) {
		for (j=0; j<125; j++){;}
    }
}