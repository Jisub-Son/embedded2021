#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "colorled.h"

int main(void)
{
	pwmLedInit();
	
	pwmLedRed(); //빨간색 표시 
	sleep(1);
	pwmLedBlue();//파란색 표시 
	sleep(1);
	pwmLedGreen();//초록색 표시 
	sleep(1);
	
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				pwmLedRGB(i, j, k); //순서대로 값을 변화해가며 표시 
				sleep(1);
			}
		}
	}
	
	pwmInactiveAll();
	return 0;
}