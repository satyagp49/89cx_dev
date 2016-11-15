#ifndef __uart_89cx_h__
#define __uart_89cx_h__

#include <datatypes.h>

#define UART_RX_BUFFER_SIZE	48

void UartInit (void);
u8 UartGetChar (void);
u16 UartGetStr (u8 *msg_str, u16 len);
void UartSendStr (u8 *str);

#endif