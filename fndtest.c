#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
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

	fndCountDisp(FND_START_CNT);
    printf("count start\r\n");
	sleep(90);
	record = fndCountDisp(FND_STOP_CNT);
    printf("count stop : %d", record); // 제발 풀 되라
	
    fndOff();
    fndExit();
}
