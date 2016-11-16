
#include <string.h>
#include <arch_xyz.h>
#include <command_mode.h>
#include <led_message_scrolling.h>

static u8 CommandRxBuffer [COMMAND_RX_BUFFER_SIZE] = {0x00};


u8 Command_Selected = 0x00;
static OPERATION_MODE Current_Permission = OPERATION_MODE_MAX;

const COMMAND_ACTION_LOOKUP cmd_lookup [] = {
    {"admin", OPERATION_MODE_ADMIN, cmd_admin},
    {"set resolution", OPERATION_MODE_ADMIN, NULL},
    {"set digit", OPERATION_MODE_ADMIN, NULL},
    {"set row", OPERATION_MODE_ADMIN, NULL},
    
    {"user", OPERATION_MODE_USER, cmd_user},    

    {"set message", OPERATION_MODE_BOTH, cmd_update_message},
    {"exit", OPERATION_MODE_BOTH, NULL},
    
};


CRENDENTIAL Admin_Credential = {"4321"};
CRENDENTIAL User_Credential = {"1234"};


void CommandMode (void) {
    if (ReceiveCommand (CommandRxBuffer, COMMAND_RX_BUFFER_SIZE) > 0) {
        for (Command_Selected = 0x00; Command_Selected < (sizeof (cmd_lookup)/ (sizeof (COMMAND_ACTION_LOOKUP))); Command_Selected ++) {
            if ((strncmp (CommandRxBuffer, cmd_lookup [Command_Selected].cmd, strlen (CommandRxBuffer))) == 0x00) {
                cmd_lookup [Command_Selected].command_action ();
            }
        }
    }    
}

void cmd_admin (void) {
    u8 *send_cmd = "password:: ";

    SendCommand (send_cmd);
    
    LED_INDICATION = 0;
    if (ReceiveCommandTimeoutSec (CommandRxBuffer, COMMAND_RX_BUFFER_SIZE, 5) == 0x00) {
        send_cmd = "Timeout !!!";
        SendCommand (send_cmd);
    }
    LED_INDICATION = 1;

    if (strncmp (CommandRxBuffer, Admin_Credential.password, strlen (CommandRxBuffer)) == 0x00) {
        Current_Permission = OPERATION_MODE_ADMIN;
        send_cmd = "Admin Login Success ...";
        SendCommand (send_cmd);
    }
    else {
        send_cmd = "Admin Login Failed !!!";
    }
}

void cmd_user (void) {
    u8 *send_cmd = "password:: ";

    SendCommand (send_cmd);
    
    LED_INDICATION = 0;
    if (ReceiveCommandTimeoutSec (CommandRxBuffer, COMMAND_RX_BUFFER_SIZE, 5) == 0x00) {
        send_cmd = "Timeout !!!";
        SendCommand (send_cmd);
    }
    LED_INDICATION = 1;

    if (strncmp (CommandRxBuffer, Admin_Credential.password, strlen (CommandRxBuffer)) == 0x00) {
        Current_Permission = OPERATION_MODE_USER;
        send_cmd = "User Login Success ...";
        SendCommand (send_cmd);
    }
    else {
        send_cmd = "User Login Failed !!!";
    }
}

void cmd_update_message (void) {
    u8* send_cmd = 0x00;


    if (!(Current_Permission & cmd_lookup [Command_Selected].permission)) {
        send_cmd = "Invalid Crentials !!!!";
        SendCommand (send_cmd);
    }
    send_cmd = "Enter Message:: ";
    SendCommand (send_cmd);
    
    LED_INDICATION = 0;
    if (ReceiveCommandTimeoutSec (CommandRxBuffer, COMMAND_RX_BUFFER_SIZE, 5) == 0x00) {
        send_cmd = "Timeout !!!";
        SendCommand (send_cmd);
    }
    LED_INDICATION = 1;

    DisableInterrupts ();
    UpdateScrollMessage (CommandRxBuffer);
    EnableInterrupts ();
    
    send_cmd = "Updated Successfully ...";
    SendCommand (send_cmd);

}