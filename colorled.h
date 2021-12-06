#ifndef _COLOR_LED_DRV_H_
#define _COLOR_LED_DRV_H_

int pwmActiveAll(void);
int pwmInactiveAll(void);
int pwmSetDuty(int dutyCycle, int pwmIndex);
int pwmSetPeriod(int Period, int pwmIndex);
int pwmSetPercent(int percent, int ledColor);
int pwmStartAll(void);
int pwmLedInit(void);
int pwmLedRed(void);
int pwmLedBlue(void);
int pwmLedGreen(void);
int pwmLedRGB(int Red, int Green, int Blue); // RGB(0 or 1) 조합으로 led 출력

#endif
