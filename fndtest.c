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
    fndInit();
    printf("Init complete!\r\n");

    fndDisp(555555, 0);
    sleep(1);
    fndOff();

    fndStaticDisp(123456);
    sleep(1);
    fndOff();
    fndStaticDisp(2510);
    sleep(1);
    fndOff();
    fndStaticDisp(2533);
    sleep(1);
    fndOff();

    fndTimeDisp();
    sleep(4);
    fndOff();

	fndCountDisp();
	BUTTON_MSG_T buttonRxData;
	switch (buttonRxData.keyInput)
			{
				case KEY_HOME: fndOff(); break;
				case KEY_SEARCH: fndCountDisp(); break;
			}
    //fndCountDisp();
    //case KEY_HOME:
	//	fndOff();
    //sleep(4);
    //fndOff();
    
    fndExit();
}
