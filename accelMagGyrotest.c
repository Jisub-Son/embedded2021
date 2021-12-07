#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/msg.h>
#include <pthread.h>
#include "accelMagGyro.h"

int main(void)
{
    ACCEL_MAG_GYRO_MSG_T RxData;
    int msgID;

    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1){
        printf("Cannot get msgID\r\n");
        return -1;
    }
    printf("check msgget\r\n");

    AccelInit();
    MagInit();
    GyroInit();
    printf("check initialize\r\n");

    int fd = open("gyrodata.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd < 0){
        printf("file open error!\r\n");
        return -1;
    }
    printf("check file open\r\n");

    int count = 0;
    while(1)
    {   
        int returnValue = 0;
        returnValue = msgrcv(msgID, &RxData, sizeof(RxData.data), 0, IPC_NOWAIT); // 비었어도 리턴
        count++;
        if(returnValue == -1) break;    // 비었으면 -1 리턴하기 때문
        printf("%d trash message Comes : [%d]\r\n", count, RxData.data);
    }
    printf("Lets get Gyro Data\r\n");
    
    while(1)
    {
        accelMagGyroGetData(GYRO);
        printf("function done\r\n");
        msgrcv(msgID, &RxData, sizeof(RxData.data), 0, 0);
        printf ("Gyro at test file %d, %d, %d\r\n",RxData.data[0],RxData.data[1],RxData.data[2]);
        dprintf(fd, "Gyro : %d\t%d\t%d\r\n", RxData.data[0], RxData.data[1], RxData.data[2]);
        sleep(1);
    }

    // 이번에도 안되는거냐

    // for(int i=0; i<10; i++){
    //     printf("accel start\r\n");
    //     accelMagGyroGetData(ACCEL);
    //     sleep(1);
    // }
    
    // for(int i=0; i<10; i++){
    //     printf("mag start\r\n");
    //     accelMagGyroGetData(MAG);
    //     sleep(1);
    // }

    // for(int i=0; i<10; i++){
    //     printf("gyro start\r\n");
    //     accelMagGyroGetData(GYRO);
    //     sleep(1);
    // }

    return 0;
}