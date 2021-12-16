#ifndef _LED_H_
#define _LED_H_

int ledLibInit(void);
int ledOnOff(int ledNum, int onOff);
int ledStatus(void);
int ledLibExit(void);
int ledifAns(void);
int ledControl(const char data[]);

#define LED_DRIVER_NAME "/dev/periled"
#define MAX_LED_NUM 8

#endif
