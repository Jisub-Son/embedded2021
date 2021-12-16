#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/kd.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include <dirent.h>

#include "led.h"
#include "button.h"
#include "buzzer.h"
#include "fnd.h"
#include "textlcd.h"
#include "colorled.h"
#include "temperature.h"
#include "accelMagGyro.h"
#include "../bmp/libbmp.h"
#include "../bmp/touch.h"
#include "games.h"

static BUTTON_MSG_T buttonRxData;
static int msgID;

int main(void)  // Main Menu
{
    int exit = 0;
    
    /*===========터치스크린 깨짐방지=====================*/
    int conFD = open ("/dev/tty0", O_RDWR);
    ioctl(conFD, KDSETMODE, KD_GRAPHICS);
    close (conFD);

    //Init
    GameInit();

    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1){
        printf("Cannot get msgID\r\n");
        return -1;
    }

    //Main Menu Image
    print_bmp("./proj_image/start.bmp");
    textlcdWrite(1, "project test");
    printf("main image loaded\r\n");

    while(1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input
        printf("main button rcv : %d\r\n", buttonRxData.pressed);
        
        if(buttonRxData.pressed){
            switch (buttonRxData.keyInput)
            {
                case KEY_VOLUMEUP:
                    printf("Volume up key\r\n");
                    // GameTime(GAME_START);
                    Level1();
                    Level2();
                    Level3();
                    Level4();
                    Level5();
                    // GameTime(GAME_STOP);
                    break;
                case KEY_HOME: 
                    printf("Home key\r\n"); 
                    break;
                case KEY_SEARCH: 
                    printf("Search key\r\n");
                    break;
                case KEY_BACK: 
                    printf("Back key\r\n"); 
                    break;
                case KEY_MENU: 
                    printf("Menu key\r\n"); 
                    break;
                case KEY_VOLUMEDOWN: 
                    printf("Volume down key\r\n"); 
                    exit = 1;
                    break;
            }
        }
        if(exit) break;
    }

    //Exit
    GameExit();
    return 0;
}