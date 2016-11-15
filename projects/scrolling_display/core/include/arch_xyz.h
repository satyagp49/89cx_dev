#ifndef __arch_xyz_h__
#define __arch_xyz_h__

#include <arch_89cx.h>

#define COMMAND_RX_BUFFER_SIZE UART_RX_BUFFER_SIZE

#define controller_init controller_init_89cx
#define peripheral_init peripheral_init_89cx
#define DisableInterrupts DisableInterrupts_89cx
#define EnableInterrupts EnableInterrupts_89cx

#define timer_init timer_init_89cx
#define DelayMs DelayMs_89cx 

#define SendCommand SendCommand_89cx
#define ReceiveCommand ReceiveCommand_89cx

#define LedSendMessage LedSendMessage_89cx
#define LedMoveToNextLine LedMoveToNextLine_89cx
#define LedResetLine LedResetLine_89cx

#endif