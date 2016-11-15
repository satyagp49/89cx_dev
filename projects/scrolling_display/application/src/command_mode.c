
#include <string.h>
#include <arch_xyz.h>
#include <command_mode.h>

static u8 CommandRxBuffer [COMMAND_RX_BUFFER_SIZE] = {0x00};

u8 Command_Selected = 0x00;
static OPERATION_MODE Current_Mode = OPERATION_MODE_MAX;
const COMMAND_ACTION_LOOKUP cmd_lookup [] = {
	{"admin", OPERATION_MODE_ADMIN, cmd_admin},
    	
};

void CommandMode (void) {
	if (ReceiveCommand (CommandRxBuffer, COMMAND_RX_BUFFER_SIZE) > 0) {
		for (Command_Selected = 0x00; Command_Selected < (sizeof (cmd_lookup)/ (sizeof (COMMAND_ACTION_LOOKUP))); Command_Selected ++) {
			if ((strncmp (CommandRxBuffer, cmd_lookup [Command_Selected].cmd, strlen (CommandRxBuffer))) == 0x00) {
				cmd_lookup [Command_Selected].command_action ();
                Current_Mode = OPERATION_MODE_MAX;
			}
		}
	}	
}

void cmd_admin (void) {
    u8 *send_cmd = "password";

    Current_Mode = cmd_lookup [Command_Selected].permission;
    SendCommand (send_cmd);
    
    LED_INDICATION = 0;
    if (ReceiveCommandTimeoutSec (CommandRxBuffer, COMMAND_RX_BUFFER_SIZE, 5) == 0x00) {
        DBG_MSG ("Rx Timeout !!!!\n");
    }
    else {
        DBG_MSG ("RxCmd:: %s\n", CommandRxBuffer);
    }
    LED_INDICATION = 1;
}
