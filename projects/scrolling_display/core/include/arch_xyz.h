#ifndef __arch_xyz_h__
#define __arch_xyz_h__

#include <arch_89cx.h>

#define controller_init controller_init_89cx
#define peripheral_init peripheral_init_89cx

#define timer_init timer_init_89cx
#define DelayMs DelayMs_89cx 

#define LedSendMessage LedSendMessage_89cx
#define LedMoveToNextLine LedMoveToNextLine_89cx
#define LedResetLine LedResetLine_89cx

#endif