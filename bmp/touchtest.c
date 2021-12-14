#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "touch.h"

int main(void)
{
    touchInit();

    int msgID = msgget(TMESSAGE_ID, IPC_CREAT|0666);
    TOUCH_MSG_T rcvMsg;

    while(1)
    {
        msgrcv(msgID, &rcvMsg, sizeof(rcvMsg)-sizeof(long int), 0, 0);

        switch (rcvMsg.keyInput)
        {
        case 999:
            printf("x : %d/t y : %d\r\n", rcvMsg.x, rcvMsg.y);
            break;
        
        default:
            break;
        }
    }
}