#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/msg.h>
#include "accelMagGyro.h"

static int fd = 0;
static FILE *fp = NULL;
static int msgID;
static pthread_t accelMagGyroTh_id;
static ACCEL_MAG_GYRO_MSG_T TxData;

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

    msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    if(msgID == -1){
        printf("Cannot get msgID\r\n");
        return -1;
    }
    TxData.messageNum = 1;
}

int accelMagGyroGetData(int sensor)     // getData from sensor
{
    switch (sensor)
    {
    case ACCEL:
        fp = fopen (ACCELPATH "data", "rt");
        int accel[3];
        fscanf(fp,"%d, %d, %d",&accel[0],&accel[1],&accel[2]);
        // printf ("I read Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
        fclose(fp);
        
        TxData.data[0] = accel[0];
        TxData.data[1] = accel[1];
        TxData.data[2] = accel[2];
        msgsnd(msgID, &TxData, sizeof(TxData.data), 0);

        break;

    case MAG:
        fp = fopen (MAGNEPATH "data", "rt");
        int magne[3];
        fscanf(fp,"%d, %d, %d",&magne[0],&magne[1],&magne[2]);
        // printf ("I read Magneto %d, %d, %d\r\n",magne[0],magne[1],magne[2]);
        fclose(fp);

        TxData.data[0] = magne[0];
        TxData.data[1] = magne[1];
        TxData.data[2] = magne[2];
        msgsnd(msgID, &TxData, sizeof(TxData.data), 0);

        break;

    case GYRO:
        fp = fopen (GYROPATH "data", "rt");
        int gyro[3];
        fscanf(fp,"%d, %d, %d",&gyro[0],&gyro[1],&gyro[2]);
        printf ("I read Gyroscope %d, %d, %d\r\n",gyro[0],gyro[1],gyro[2]);
        
        TxData.data[0] = gyro[0];
        TxData.data[1] = gyro[1];
        TxData.data[2] = gyro[2];

        fclose(fp);
        
        msgsnd(msgID, &TxData, sizeof(TxData.data), 0);

        break;

    default:
        printf("Wrong Value : select ACCEL, MAG, GYRO\r\n");
        break;
    }
}
// 제발 되라