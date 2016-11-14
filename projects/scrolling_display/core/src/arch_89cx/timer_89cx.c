
#include <timer_89cx.h>
#include <REG51.H>


void (*isr_callback)();

void timer_init_89cx (void (*isr_handler)())
{
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
	isr_callback = isr_handler;
}	  

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
static void timer0_isr (void);
This function is an interrupt service routine for TIMER 0. It should never
be called by a C or assembly function. It will be executed automatically
when TIMER 0 overflows.
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
void timer0_isr (void) interrupt 1
{
	unsigned int itmp;
	/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	Stop Timer 0, adjust the timer 0 counter so that
	we get another interrupt in 10ms, and restart the
	timer.
	=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
	TR0 = 0; /* stop timer 0 */
	itmp = TIMER0_COUNT + TL0 + (TH0<<8);
	TL0 = itmp;
	TH0 = itmp >> 8;

	isr_callback();

	TR0 = 1; /* start timer 0 for next cycle s*/
}

void DelayMs_89cx (unsigned int x)	 // delays x msec (at fosc=11.0592MHz)
{
	unsigned char j=0;
	while(x-- > 0)
	{
		for (j=0; j<125; j++){;}
	}
}