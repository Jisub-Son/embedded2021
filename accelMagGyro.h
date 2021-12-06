#ifndef _ACCEL_MAG_GYRO_H_
#define _ACCEL_MAG_GYRO_H_

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

#define ACCEL 0
#define MAG 1
#define GYRO 2

int AccelInit(void);     // initialize Accel
int MagInit(void);     // initialize Mag
int GyroInit(void);     // initialize Gyro
int accelMagGyroGetData(int sensor);     // getData from sensor
// int accelMagGyroExit(void);     // exit 필요없을 수도

#endif