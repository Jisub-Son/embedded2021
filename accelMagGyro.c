#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "accelMagGyro.h"

static int fd = 0;
static FILE *fp = NULL;
// static int msgID;
// static pthread_t accelMagGyroTh_id;
// static ACCEL_MAG_GYRO_MSG_T TxData;

int AccelInit(void)     // initialize Accel
{
    fd = open (ACCELPATH "enable",O_WRONLY);
    dprintf (fd,"1");
    close(fd);
    return 0;
}

int MagInit(void)     // initialize Mag
{
    fd = open (MAGNEPATH "enable",O_WRONLY);
    dprintf (fd,"1");
    close(fd);
    return 0;
}

int GyroInit(void)     // initialize Gyro
{
    fd = open (GYROPATH "enable",O_WRONLY);
    dprintf (fd,"1");
    close(fd);
    return 0;

    // msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    // if(msgID == -1){
    //     printf("Cannot get msgID\r\n");
    //     return -1;
    // }
    // TxData.messageNum = 1;
}

int accelMagGyroGetData(int sensor)     // get Data from sensor
{
    switch (sensor)
    {
    case ACCEL:
        fp = fopen (ACCELPATH "data", "rt");
         
        fscanf(fp,"%d, %d, %d",&sensorData[0],&sensorData[1],&sensorData[2]);
        printf ("I read Accel %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
       
        fclose(fp);
        break;

    case MAG:
        fp = fopen (MAGNEPATH "data", "rt");
        
        fscanf(fp,"%d, %d, %d",&sensorData[0],&sensorData[1],&sensorData[2]);
        printf ("I read Mag %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
       
        fclose(fp);
        break;

    case GYRO:
        fp = fopen (GYROPATH "data", "rt");
        
        fscanf(fp,"%d, %d, %d",&sensorData[0],&sensorData[1],&sensorData[2]);
        printf ("I read Gyroscope %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
       
        fclose(fp);
        break;

    default:
        printf("Wrong Value : select ACCEL, MAG, GYRO\r\n");
        break;
    }
}

int AccelExit(void)     // exit Accel
{
    fd = open (ACCELPATH "enable",O_WRONLY);
    dprintf (fd,"0");
    close(fd);
    return 0;
}

int MagExit(void)     // exit Mag
{
    fd = open (MAGNEPATH "enable",O_WRONLY);
    dprintf (fd,"0");
    close(fd);
    return 0;
}

int GyroExit(void)     // exit Gyro
{
    fd = open (GYROPATH "enable",O_WRONLY);
    dprintf (fd,"0");
    close(fd);
    return 0;
}