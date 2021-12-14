#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

int main(void)
{   
    BUTTON_MSG_T buttonRxData;
    int msgID;

    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1){
        printf("Cannot get msgID\r\n");
        return -1;
    }
    
    buttonInit();
    printf("init finished\r\n");

    while(1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);

        //printf("returnValue : %d\r\n", returnValue);

        switch (buttonRxData.keyInput)
        {
            case KEY_VOLUMEUP: printf("Volume up key :"); break;
            case KEY_HOME: printf("Home key :"); break;
            case KEY_SEARCH: printf("Search key :"); break;
            case KEY_BACK: printf("Back key :"); break;
            case KEY_MENU: printf("Menu key :"); break;
            case KEY_VOLUMEDOWN: printf("Volume down key :"); break;
        }
        if(buttonRxData.pressed) printf(" pressed\r\n");
        else printf(" released\r\n");
    }

    buttonExit();
    return 0;
}
