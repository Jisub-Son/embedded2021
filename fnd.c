#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "fnd.h"
#include "button.h"

#include <linux/input.h>
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>

#define FND_DRIVER_NAME "/dev/perifnd"

static int fd;
static stFndWriteForm stWriteData;

int fndInit(void)
{
    fd = open(FND_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver open error.\n");
		return 0;
	}	
}

int fndDisp(int num , int dotflag)
{
	// int fd;
	int temp,i;
	// stFndWriteForm stWriteData;
	
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

	// fd = open(FND_DRIVER_NAME,O_RDWR);
	// if ( fd < 0 )
	// {
	// 	perror("driver open error.\n");
	// 	return 0;
	// }	
	write(fd,&stWriteData,sizeof(stFndWriteForm));
	// close(fd);
	return 1;
}

int fndOff(void)
{
	int i;
	// stFndWriteForm stWriteData;
	
	for (i = 0; i < MAX_FND_NUM ; i++ )
	{
		stWriteData.DataDot[i] =  0;  
		stWriteData.DataNumeric[i] = 0;
		stWriteData.DataValid[i] = 0;
	}
	// fd = open(FND_DRIVER_NAME,O_RDWR);
	// if ( fd < 0 )
	// {
	// 	perror("driver open error.\n");
	// 	return 0;
	// }	
	write(fd,&stWriteData,sizeof(stFndWriteForm));
	// close(fd);
	return 1;
}

int fndStaticDisp(int num)
{
    fndDisp(num, 0);
}

int fndTimeDisp(void)
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
/*
int fndCountDisp(int number)
{
    int counter = 0;
    while(1)
		{
			if (!fndDisp(counter , 0))
				break;

			counter++;
			sleep(1);
			if (counter > number )
				break;
		}
}
*/

int fndCountDisp(void)
{
    int counter = 0;
    while(1)
		{
			if (!fndDisp(counter , 0))
				break;

			counter++;
			sleep(1);
			
		}
}

int fndExit(void)
{
    fndOff();
    close(fd);
}

