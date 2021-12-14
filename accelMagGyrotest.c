#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "accelMagGyro.h"

int main(void)
{
    AccelInit();
    MagInit();
    GyroInit();
    printf("Initialize complete\r\n");

    // int fd = open("gyrodata.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    // if(fd < 0){
    //     printf("file open error!\r\n");
    //     return -1;
    // }
    // printf("check file open\r\n");

    for(int i=0; i<5; i++){
        accelMagGyroGetData(ACCEL);
        printf ("Accel at test file %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
        sleep(1);
    }

    for(int i=0; i<5; i++){
        accelMagGyroGetData(MAG);
        printf ("Mag at test file %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
        sleep(1);
    }

    for(int i=0; i<5; i++){
        accelMagGyroGetData(GYRO);
        printf ("Gyro at test file %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
        sleep(1);
    }

    // while(1)
    // {
    //     accelMagGyroGetData(GYRO);
    //     printf("function done\r\n");
    //     printf ("Gyro at test file %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
    //     dprintf(fd, "Gyro : %d\t%d\t%d\r\n", sensorData[0], sensorData[1], sensorData[2]);
    //     sleep(1);
    // }

    AccelExit();
    MagExit();
    GyroExit();

    return 0;
}
