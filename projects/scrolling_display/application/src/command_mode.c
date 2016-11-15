
#include <string.h>
#include <arch_xyz.h>
#include <command_mode.h>

static u8 CommandRxBuffer [COMMAND_RX_BUFFER_SIZE] = {0x00};
const COMMAND_ACTION_LOOKUP cmd_lookup [] = {
	{"admin", cmd_admin},
	
};

void CommandMode (void) {
	u8 count = 0x00;
	if (ReceiveCommand (CommandRxBuffer, (COMMAND_RX_BUFFER_SIZE - 1)) > 0) {
        SendCommand (CommandRxBuffer);
		for (count = 0x00; count < (sizeof (cmd_lookup)/ (sizeof (COMMAND_ACTION_LOOKUP))); count ++) {
			if ((strncmp (CommandRxBuffer, cmd_lookup [count].cmd, strlen (CommandRxBuffer))) == 0x00) {
				DisableInterrupts ();
				cmd_lookup [count].command_action ();
				EnableInterrupts ();
			}
		}
	}	
}

void cmd_admin (void) {
    u8 *send_cmd = "password";

    SendCommand (send_cmd);
}
