#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "colorled.h"
/*
int main(int argc, char *argv[]) 
{
	if (argc != 4)
	{ 
		printf ("colorledtest.elf 0-100 0-100 0-100\r\n");
		printf ("ex) colorledtest.elf 100 100 100 ==> full white color\r\n");
		return 0; 
	}
	pwmLedInit();
	pwmSetPercent(atoi(argv[1]),0);
	pwmSetPercent(atoi(argv[2]),1);
	pwmSetPercent(atoi(argv[3]),2);
	pwmInactiveAll();
	return 0;
}
*/


int main(void)
{
	pwmLedInit();
	
	pwmLedRed();
	sleep(1);
	pwmLedBlue();
	sleep(1);
	pwmLedGreen();
	sleep(1);
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				pwmLedRGB(i, j, k);
				sleep(1);
			}
		}
	}

	pwmInactiveAll();
	return 0;
}

