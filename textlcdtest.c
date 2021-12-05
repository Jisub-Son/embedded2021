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
#include <time.h>
#include "textlcd.h"

int main(void)
{
    textlcdInit();

    textlcdWrite(1, " does it works? ");
    textlcdWrite(2, "    really??    ");
    sleep(1);

    textlcdWrite(1, "  60172510 Son  ");
    textlcdWrite(2, "  60172533 Iim  ");
    sleep(1);

    for(int i = 1; i < 8; i++){
        textlcdTime(1);
        printf("Time : %d\r\n", i);
        textlcdlevel(2, i);
        printf("leveltest : %d\r\n", i);
        sleep(1);
    }
    
    textlcdExit();
    return 0;
}