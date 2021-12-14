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
#include "games.h"

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
    BUTTON_MSG_T buttonRxData;
    int msgID;

    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1){
        printf("Cannot get msgID\r\n");
        return -1;
    }

    // trash msg
    int count;
    while(1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, IPC_NOWAIT); // 비었어도 리턴

        if(returnValue == -1) break;    // 비었으면 -1 리턴하기 때문
        count++;
        printf("%d trash message Comes : [%d]\r\n", count, buttonRxData.keyInput);
    }

    printf("\tI got %d messages in the queue\r\n", count);

    //초기 이미지 띄워야 함
    print_bmp("flower.bmp");
    printf("main image loaded\r\n");

    textlcdWrite(1, "project test");
    
    while(1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input

        textlcdTime(2);

        switch (buttonRxData.keyInput)
        {
            case KEY_VOLUMEUP:
                printf("Volume up key\r\n"); 
                ledOnOff(1, 1);
                buzzerPlaySongforMsec(buzzermusicScale[0], 500);
                fndStaticDisp(1111);
                pwmLedRGB(1, 0, 0);
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