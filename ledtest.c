#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"

#define LED_DRIVER_NAME     "/dev/periled"

int main(void)
{
    int ledNum = 0;
    int ledStat = 0;
    int i=0;

    ledLibInit();   // led initailize


	for (i=0;i<8;i++)
	{
		ledOnOff(i, 1);
		sleep(1);
		ledStat = ledStatus();
		printf("ledStatus is : %08x\n", ledStat);		
		ledOnOff(i,0);
	}

    



    sleep(1);

    ledLibExit();

    return 0;
}

