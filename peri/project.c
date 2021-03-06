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
    int game_time = 0;

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
    textlcdWrite(1, " Welcome to Emb ");
    textlcdWrite(2, "  Press Vol.up  ");
    printf("main image loaded\r\n");

    while(1)
    {
        textlcdWrite(1, " Welcome to Emb ");
        textlcdWrite(2, "  Press Vol.up  ");
        int returnValue = 0;
        returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input
        printf("main button rcv : %d\r\n", buttonRxData.pressed);
        
        if(buttonRxData.pressed){
            switch (buttonRxData.keyInput)
            {
                case KEY_VOLUMEUP:
                    printf("Volume up key\r\n");
                    fndCountDisp(FND_START_CNT);
                    Level1();
                    Level2();
                    Level3();
                    Level4();
                    Level5();
                    Level6();
                    game_time = fndCountDisp(FND_STOP_CNT);
                    Ranking(game_time);
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
