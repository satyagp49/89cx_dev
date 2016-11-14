#include <arch_89cx.h>
#define UART_RX_BUFFER_SIZE	50 
static u8 UartRxBuffer [UART_RX_BUFFER_SIZE] = {0x00};
static u8 UartGetCount = 0x00;
static u8 UartPutCount = 0x00;
u8 UartBufferIsEmpty = 0x00;

static u8 UartGetChar (void) {
    u8 ret_val = 0x00;
	if (UartGetCount == UartPutCount) {
		UartBufferIsEmpty = 0x01;
		ret_val = 0xFF;
	}
	else {  
		ret_val = UartRxBuffer [UartGetCount++];
		if (UartGetCount >= UART_RX_BUFFER_SIZE) {
			UartGetCount = 0x00;
		}
		if (UartGetCount == UartPutCount) {
			UartGetCount = UartPutCount = 0x00;
		}
	}
	return ret_val;
}
u16 uart_get_str (u8 *msg_str, u16 len) {
	u16 count = 0x00;
	do {
		if (!UartBufferIsEmpty) {
			msg_str [count ++] = UartGetChar ();
		}
	} while ((!UartBufferIsEmpty) && (count < len));
	return count;
}	
u8 uart_get_char (void) {
    if (!UartBufferIsEmpty) {
		return UartGetChar ();
	}
    return 0x00;
}	

void serial_isr (void) interrupt 4
{
    if (RI == 1)       /* it was a receive interrupt */
    {
		LED_INDICATION = 0x00;
		DelayMs_89cx (2);
		LED_INDICATION = 0x01;
		DelayMs_89cx (2);
        /* read the character into our local buffer */
		UartBufferIsEmpty = 0x00;
		UartRxBuffer [UartPutCount++] = SBUF;
		if (UartPutCount >= UART_RX_BUFFER_SIZE) {
			UartPutCount = 0x00; 
		}
		if (UartPutCount + 1 == UartGetCount) {
			UartGetCount++;
			if (UartGetCount >= UART_RX_BUFFER_SIZE) {
				UartGetCount = 0x00;
			}
		}		

        RI = 0;        /* clear the received interrupt flag */
        TI = 1;        /* signal that there's a new character to send */
    }	
}

void uart_init (void) {
	//9600 bps @ 11.059 MHz
	SCON = 0x50; /* Setup serial port control register */
	/* Mode 1: 8-bit uart var. baud rate */
	/* REN: enable receiver */
	PCON &= 0x7F; /* Clear SMOD bit in power ctrl reg */
	/* This bit doubles the baud rate */
	TMOD &= 0xCF; /* Setup timer/counter mode register */
	/* Clear M1 and M0 for timer 1 */
	TMOD |= 0x20; /* Set M1 for 8-bit autoreload timer */
	TH1 = 0xFD; /* Set autoreload value for timer 1 */
	/* 9600 baud with 11.0592 MHz xtal */
	TR1 = 1; /* Start timer 1 */
	TI = 1; /* Set TI to indicate ready to xmit */
	ES  = 1;                /* allow serial interrupts */
	EA  = 1;                /* enable interrupts */
}

void controller_init_89cx (void) {
    
}

void peripheral_init_89cx (void) {
    uart_init ();
}

    
void LedSendMessage_89cx (u8 led_msg) {
    u8 count = 0x00;
    
    for (count = 0x00; count < LED_DIGIT_WIDTH; count ++) {
        printf ("%x", (led_msg >> count) & 0x01);
    }
    printf ("\t");
}

void LedMoveToNextLine_89cx (void) {
    printf (">>>>\n");
}

void LedResetLine_89cx (void) {
    printf ("----------\n");
}