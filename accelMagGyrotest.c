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

    while(1)
    {
        accelMagGyroGetData(GYRO);
        printf("function done\r\n");
        printf ("Gyro at test file %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
        dprintf(fd, "Gyro : %d\t%d\t%d\r\n", sensorData[0], sensorData[1], sensorData[2]);
        sleep(1);
    }



    return 0;
}
