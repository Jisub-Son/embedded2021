#ifndef _ACCEL_MAG_GYRO_H_
#define _ACCEL_MAG_GYRO_H_

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

#define ACCEL 0
#define MAG 1
#define GYRO 2

int sensorData[3];      // 전역변수에 데이터 저장

int AccelInit(void);     // initialize Accel
int MagInit(void);     // initialize Mag
int GyroInit(void);     // initialize Gyro
int accelMagGyroGetData(int sensor);     // get Data from sensor
int AccelExit(void);     // exit Accel
int MagExit(void);     // exit Mag
int GyroExit(void);     // exit Gyro

#endif
