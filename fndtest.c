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

    fndDisp(123456, 0); //123456출력 
    sleep(1);
    // fndOff();

    fndStaticDisp(6017); //006017출력 
    sleep(1);
    // fndOff();

    for(int i = 0; i < 8; i++){
        fndTimeDisp(); //현재 시간 출력 
        sleep(1);
        // fndOff();
    }

	fndCountDisp(FND_START_CNT); //카운트 업 
    printf("count start\r\n");
	sleep(90);
	record = fndCountDisp(FND_STOP_CNT); //카운트 업 멈춤 
    printf("count stop : %d", record); 
	
    fndOff();
    fndExit();
}
