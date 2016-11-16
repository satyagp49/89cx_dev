
#include <arch_89cx.h>
#include <string.h>

static u8 UartRxBuffer [UART_RX_BUFFER_SIZE] = {0x00};
static u8 UartGetCount = 0x00;
static u8 UartPutCount = 0x00;
static u8 IsUartBufferEmpty = 0x01;

void clear_uart_buffer (void) {
    UartGetCount = 0x00;
    UartPutCount = 0x00;
    IsUartBufferEmpty = 0x01;
    memset (UartRxBuffer, 0x00, UART_RX_BUFFER_SIZE);
}
void serial_isr (void) interrupt 4
{
    EA = 0;
    if (RI == 1)       /* it was a receive interrupt */
    {
        /* read the character into our local buffer */
		IsUartBufferEmpty = 0x00;
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
    EA  = 1;
}

void UartInit (void) {
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

u8 UartGetChar (void) {
    u8 ret_val = 0x00;
	if (UartGetCount == UartPutCount) {
		IsUartBufferEmpty = 0x01;
		ret_val = 0xFF;
	}
	else {  
		ret_val = UartRxBuffer [UartGetCount++];
		if (UartGetCount >= UART_RX_BUFFER_SIZE) {
			UartGetCount = 0x00;
		}
		if (UartGetCount == UartPutCount) {
            IsUartBufferEmpty = 0x01;
			UartGetCount = UartPutCount = 0x00;
		}
	}
	return ret_val;
}

u16 UartGetStr (u8 *msg_str, u16 len) {
	u16 count = 0x00;
	do {
        if ((count == 0x00) && (IsUartBufferEmpty)) {
            DelayMs_89cx (2);   // wait till whole message to come
        }
		if (!IsUartBufferEmpty) {
			msg_str [count] = UartGetChar ();
            if ((msg_str [count] == '\r') || (msg_str [count] == '\n')) {
                msg_str [count] = '\0';
                return count;
            }
            count ++;
		}
	} while ((!IsUartBufferEmpty) && (count < len));
    if (count < len) {
        msg_str [count] = 0x00;
    }
	return count;
}	

u16 UartGetStrTimeoutSec (u8 *msg_str, u16 len, u8 time_out) {
	u16 count = 0x00;
    s16 timeout_loop = (time_out * 10);

    clear_uart_buffer ();

    while ((timeout_loop > 0) && (IsUartBufferEmpty)) {
        DelayMs_89cx (100);
        timeout_loop --;
    }
    if (timeout_loop <= 0x00) {
        return 0;
    }
    
    count = 0x00;

	do {
		if (!IsUartBufferEmpty) {
			msg_str [count] = UartGetChar ();
            if ((msg_str [count] == '\r') || (msg_str [count] == '\n')) {
                msg_str [count] = '\0';
                return count;
            }
            count ++;
		}
	} while ((!IsUartBufferEmpty) && (count < len));
    if (count < len) {
        msg_str [count] = 0x00;
    }
	return count;
}	

void UartSendStr (const u8 *str) {
    printf ("%s\r\n", str);
}

