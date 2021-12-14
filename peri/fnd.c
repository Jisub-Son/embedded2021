#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "fnd.h"


#define FND_DRIVER_NAME "/dev/perifnd"

static int fd, counter = 0, state;
static stFndWriteForm stWriteData;
static pthread_t fndTh_id;

int fndInit(void) 
{
    fd = open(FND_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver open error.\n");
		return 0;
	}	
}

int fndDisp(int num , int dotflag) //fnd자리수 나뉘어서 출력되게 설정 
{
	int temp,i;
	
	for (i = 0; i < MAX_FND_NUM ; i++ )
	{
		stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;  
		stWriteData.DataValid[i] = 1;
	}
	// if 6 fnd
	temp = num % 1000000;	stWriteData.DataNumeric[0] = temp / 100000;
	temp = num % 100000;	stWriteData.DataNumeric[1] = temp / 10000;
	temp = num % 10000;		stWriteData.DataNumeric[2] = temp / 1000;
	temp = num % 1000;		stWriteData.DataNumeric[3] = temp / 100;
	temp = num % 100;		stWriteData.DataNumeric[4] = temp / 10;
							stWriteData.DataNumeric[5] = num % 10;

	write(fd,&stWriteData,sizeof(stFndWriteForm));
	return 1;
}

int fndOff(void)
{
	int i;
	
	for (i = 0; i < MAX_FND_NUM ; i++ )
	{
		stWriteData.DataDot[i] =  0;  
		stWriteData.DataNumeric[i] = 0;
		stWriteData.DataValid[i] = 0;
	}

	write(fd,&stWriteData,sizeof(stFndWriteForm));
	return 1;
}

int fndStaticDisp(int num) //숫자 계속 켜두기 
{
    fndDisp(num, 0);
}

int fndTimeDisp(void) //현재시간 표시 
{
    int number;
    struct tm *ptmcur;
		time_t tTime;
		if ( -1 == time(&tTime) )
			return -1; 

		ptmcur = localtime(&tTime);

		number = ptmcur->tm_hour * 10000;
		number += ptmcur->tm_min *100;
		number += ptmcur->tm_sec;

		fndDisp(number , 0b1010);
}

void fndThFunc(void) //시,분,초로 보여지게 설정 
{	
	int number;

	while(1){
		number = (counter / 3600) * 10000;
		number += (counter / 60) * 100;
		number += counter % 60;
		
		if(!fndDisp(number, 0b1010))
			break;

		if(state == FND_STOP_CNT)
			pthread_exit(NULL);

		counter++;
		printf("counter : %d\r\n", counter);
		sleep(1);
	}
}

int fndCountDisp(int run) //카운트업 설정 
{
	int err;
	
	state = run;
	if(run == FND_START_CNT){		// start이면 쓰레드 생성하여 counter 동작
		err = pthread_create(&fndTh_id, NULL, &fndThFunc, NULL);
		if(err != 0){
			printf("Thread Create Error : [%d]\r\n", err);
		}
		pthread_detach(fndTh_id);
	}
	else if(run == FND_STOP_CNT){	// stop이면 쓰레드 종료
		return counter;
	}
}

int fndExit(void)
{
    fndOff();
    close(fd);
}

