#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "colorled.h"
#define COLOR_LED_DEV_R_ "/sys/class/pwm/pwmchip0/"
#define COLOR_LED_DEV_G_ "/sys/class/pwm/pwmchip1/"
#define COLOR_LED_DEV_B_ "/sys/class/pwm/pwmchip2/"
#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_DUTY "pwm0/duty_cycle"
#define PWM_PERIOD "pwm0/period"
#define PWM_ENABLE "pwm0/enable"
#define PWM_COLOR_R 0
#define PWM_COLOR_G 1
#define PWM_COLOR_B 2
#define PWM_PERIOD_NS 1000000

int pwmActiveAll(void)
{
	int fd = 0;
	fd = open( COLOR_LED_DEV_R_ PWM_EXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	fd = open( COLOR_LED_DEV_G_ PWM_EXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	fd = open( COLOR_LED_DEV_B_ PWM_EXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	return 1;
}

int pwmInactiveAll(void)
{
	int fd =0;
	fd = open( COLOR_LED_DEV_R_ PWM_UNEXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	fd = open( COLOR_LED_DEV_G_ PWM_UNEXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	fd = open( COLOR_LED_DEV_B_ PWM_UNEXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	return 1;
}

int pwmSetDuty(int dutyCycle, int pwmIndex)
{
	int fd = 0;
	switch (pwmIndex)
	{
		case 0:
		fd = open ( COLOR_LED_DEV_R_ PWM_DUTY, O_WRONLY);
		break;
		case 1:
		fd = open ( COLOR_LED_DEV_G_ PWM_DUTY, O_WRONLY);
		break;
		case 2:
		default:
		fd = open ( COLOR_LED_DEV_B_ PWM_DUTY, O_WRONLY);
		break;
	}
	
	dprintf(fd, "%d", dutyCycle); //열려져 있는 파일 내부에 작성한다. 
	close(fd);
	return 1;
}

int pwmSetPeriod(int Period, int pwmIndex)
{
	int fd = 0;
	switch (pwmIndex)
	{
		case 2:
		fd = open ( COLOR_LED_DEV_R_ PWM_PERIOD, O_WRONLY);
		break;
		case 1:
		fd = open ( COLOR_LED_DEV_G_ PWM_PERIOD, O_WRONLY);
		break;
		case 0:
		default:
		fd = open ( COLOR_LED_DEV_B_ PWM_PERIOD, O_WRONLY);
		break;
	}
	
	//printf ("Set pwm%d, Period:%d\r\n",pwmIndex, Period);
	dprintf(fd, "%d", Period); //열려져 있는 파일 내부에 작성 
	close(fd);
	return 1;
}

int pwmSetPercent(int percent, int ledColor)
{
	if ((percent <0) || (percent > 100))
	{
		printf ("Wrong percent: %d\r\n",percent);
		return 0;
	}

	int duty = (100- percent) * PWM_PERIOD_NS / 100; //시간 
	//LED Sinking.
	pwmSetDuty(duty, ledColor);
	return 0;
}

int pwmStartAll(void)
{
	int fd = 0;
	fd = open ( COLOR_LED_DEV_R_ PWM_ENABLE, O_WRONLY);
	write(fd,&"1",1);
	close(fd);
	fd = open ( COLOR_LED_DEV_G_ PWM_ENABLE, O_WRONLY);
	write(fd,&"1",1);
	close(fd);
	fd = open ( COLOR_LED_DEV_B_ PWM_ENABLE, O_WRONLY);
	write(fd,&"1",1);
	close(fd);
	return 1;
}

int pwmLedInit(void)
{ //Initialize
	pwmActiveAll();
	pwmSetDuty(0, 0); //R<-0
	pwmSetDuty(0, 1); //G<-0
	pwmSetDuty(0, 2); //B<-0
	pwmSetPeriod(PWM_PERIOD_NS, 0); pwmSetPeriod(PWM_PERIOD_NS, 1); pwmSetPeriod(PWM_PERIOD_NS, 2);
	pwmStartAll();
	return 0;
}
/*
int pwmLedRed(void)
{ //Initialize
	pwmActiveAll();
	pwmSetDuty(100, 0); //R<-100
	pwmSetDuty(0, 1); //G<-0
	pwmSetDuty(0, 2); //B<-0
	pwmSetPeriod(PWM_PERIOD_NS, 0); pwmSetPeriod(PWM_PERIOD_NS, 1); pwmSetPeriod(PWM_PERIOD_NS, 2);
	pwmStartAll();
	return 0;
}
*/
int pwmLedRed(void)
{
	pwmLedInit();
	
	pwmSetPercent(100,0);
	pwmSetPercent(0,1);
	pwmSetPercent(0,2);
	pwmInactiveAll();
	return 0;
}

int pwmLedGreen(void)
{ 
	pwmLedInit();
	
	pwmSetPercent(0,0);
	pwmSetPercent(100,1);
	pwmSetPercent(0,2);
	pwmInactiveAll();
	return 0;
}

int pwmLedBlue(void)
{ 
	pwmLedInit();
	
	pwmSetPercent(0,0);
	pwmSetPercent(0,1);
	pwmSetPercent(100,2);
	pwmInactiveAll();
	return 0;
}

int pwmLedRGB(int Red, int Green, int Blue) // RGB(0 or 1) 조합으로 led 출력
{	
	if(Red>1 || Green>1 || Blue>1){		// error 메세지
		printf("Wrong Value : write 0 or 1\r\n");
		return -1;
	}

	pwmSetPercent(Red*100,0);
	pwmSetPercent(Green*100,1);
	pwmSetPercent(Blue*100,2);
	return 0;
}