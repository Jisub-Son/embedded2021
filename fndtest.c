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



int main(void)
{   
    int record;

    fndInit();
    printf("Init complete!\r\n");

    fndDisp(123456, 0);
    sleep(1);
    // fndOff();

    fndStaticDisp(6017);
    sleep(1);
    // fndOff();

    for(int i = 0; i < 8; i++){
        fndTimeDisp();
        sleep(1);
        // fndOff();
    }

	fndCountDisp(0);
    printf("count start\r\n");
	sleep(10);
	record = fndCountDisp(1);
    printf("count stop : %d", record); // 제발 풀 되라
	
    fndOff();
    fndExit();
}
