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

    ledLibInit();   // led initailize

    printf("select ledNum : ");
    scanf("%d", &ledNum);

    ledOnOff(ledNum, 1);

    ledStat = ledStatus();
    printf("ledStatus is : %d\n", ledStat);

    ledLibExit();

    return 0;
}
