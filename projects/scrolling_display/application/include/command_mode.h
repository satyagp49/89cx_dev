#ifndef __command_mode_h__
#define __command_mode_h__

typedef enum operation_mode {
    OPERATION_MODE_ADMIN,
    OPERATION_MODE_USER,
    OPERATION_MODE_BOTH,

    OPERATION_MODE_MAX,
}OPERATION_MODE;

typedef struct command_action_lookup {
	u8 *cmd;
    OPERATION_MODE permission;
	void (*command_action)(void);
}COMMAND_ACTION_LOOKUP;

void CommandMode (void);

void cmd_admin (void);


#endif