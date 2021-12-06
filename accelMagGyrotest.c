#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/msg.h>
#include <pthread.h>
#include "accelMagGyro.h"

int main(void)
{
    // int accelData[3], magData[3], gyroData[3];
    ACCEL_MAG_GYRO_MSG_T RxData;
    int msgID;

    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1){
        printf("Cannot get msgID\r\n");
        return -1;
    }

    AccelInit();
    MagInit();
    GyroInit();

    int fd = open("gyrodata.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd < 0){
        printf("file open error!\r\n");
        return -1;
    }

    while(1)
    {
        accelMagGyroGetData(GYRO);
        msgrcv(msgID, &RxData, sizeof(RxData.data), 0, 0);
        printf ("I read Gyroscope %d, %d, %d\r\n",RxData.data[0],RxData.data[1],RxData.data[2]);
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