#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
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

BUTTON_MSG_T buttonRxData;
int msgID;

int main(void)  // Main Menu
{
    int exit = 0;
    //Init
    ledLibInit();
    buttonInit();
    buzzerInit();
    fndInit();
    pwmLedInit();
    textlcdInit();
    printf("Init complete\r\n");

    //Button msg setting
    GameInit();

    //초기 이미지 띄워야 함
    print_bmp("./proj_image/flower.bmp");
    printf("main image loaded\r\n");

    textlcdWrite(1, "project test");
    
    while(1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input

        textlcdTime(2);
        if(buttonRxData.pressed){
            switch (buttonRxData.keyInput)
            {
                case KEY_VOLUMEUP:
                    printf("Volume up key\r\n"); 
                    print_bmp("./proj_image/ex1.bmp");
                    Level1();
                    break;
                case KEY_HOME: 
                    printf("Home key\r\n"); 
                    ledOnOff(2, 1);
                    buzzerPlaySongforMsec(buzzermusicScale[4], 1000);
                    fndStaticDisp(222222);
                    pwmLedRGB(0, 1, 0);
                    break;
                case KEY_SEARCH: 
                    printf("Search key\r\n");
                    ledOnOff(3, 1);
                    fndTimeDisp();
                    pwmLedRGB(0, 0, 1);
                    break;
                case KEY_BACK: 
                    printf("Back key\r\n"); 
                    ledOnOff(4, 1);
                    buzzerifAns();
                    fndCountDisp(FND_START_CNT);
                    pwmLedRGB(1, 1, 0);
                    break;
                case KEY_MENU: 
                    printf("Menu key\r\n"); 
                    ledOnOff(5, 1);
                    buzzerifNotAns();
                    fndCountDisp(FND_STOP_CNT);
                    pwmLedRGB(0, 1, 1);
                    break;
                case KEY_VOLUMEDOWN: 
                    printf("Volume down key\r\n"); 
                    ledOnOff(6, 1);
                    exit = 1;
                    break;
            }
        }
        if(exit) break;
    }
        //dd
    //Exit
    ledLibExit();
    buttonExit();
    buzzerExit();
    fndExit();
    pwmInactiveAll();
    textlcdExit();
    printf("main finished!\r\n");

    return 0;
}