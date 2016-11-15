#ifndef __command_mode_h__
#define __command_mode_h__

typedef struct command_action_lookup {
	u8 *cmd;
	void (*command_action)(void);
}COMMAND_ACTION_LOOKUP;

void CommandMode (void);

void cmd_admin (void);

#endif