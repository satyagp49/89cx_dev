#ifndef __command_mode_h__
#define __command_mode_h__

#define PASSWORD_LEN 5

typedef enum operation_mode {
    OPERATION_MODE_ADMIN = 0x01,
    OPERATION_MODE_USER = 0x02,
    OPERATION_MODE_BOTH = 0x03,

    OPERATION_MODE_MAX = 0x00,
}OPERATION_MODE;

typedef struct command_action_lookup {
	u8 *cmd;
    OPERATION_MODE permission;
	void (*command_action)(void);
}COMMAND_ACTION_LOOKUP;

typedef struct crendential {
	u8 password [PASSWORD_LEN];
}CRENDENTIAL;


void CommandMode (void);

void cmd_admin (void);
void cmd_user (void);
void cmd_update_message (void);


#endif