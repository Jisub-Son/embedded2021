#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "accelMagGyro.h"

int main(void)
{
    // int accelData[3], magData[3], gyroData[3];

    AccelInit();
    MagInit();
    GyroInit();

    for(int i=0; i<10; i++){
        printf("accel start\r\n");
        accelMagGyroGetData(ACCEL);
        sleep(1);
    }
    
    for(int i=0; i<10; i++){
        printf("mag start\r\n");
        accelMagGyroGetData(MAG);
        sleep(1);
    }

    for(int i=0; i<10; i++){
        printf("gyro start\r\n");
        accelMagGyroGetData(GYRO);
        sleep(1);
    }

    return 0;
}