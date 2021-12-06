#ifndef _COLOR_LED_DRV_H_
#define _COLOR_LED_DRV_H_

int pwmActiveAll(void); //전부 활성화 
int pwmInactiveAll(void); //전부 비활성화 
int pwmSetDuty(int dutyCycle, int pwmIndex); //Duty 설정 
int pwmSetPeriod(int Period, int pwmIndex); //Period설정 
int pwmSetPercent(int percent, int ledColor); //percent로 바꿔서 원하는 색 출력 
int pwmStartAll(void);
int pwmLedInit(void);
int pwmLedRed(void);//빨강 출력 
int pwmLedBlue(void);//파랑 출력 
int pwmLedGreen(void);//초록 출력 
int pwmLedRGB(int Red, int Green, int Blue); // RGB(0 or 1) 조합으로 led 출력

#endif
