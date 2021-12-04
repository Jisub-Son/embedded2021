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
#include "textlcd.h"

int main(void)
{
    textlcdInit();

    textlcdWrite(1, " does it works? ");
    textlcdWrite(2, "    really??    ");
    sleep(1);

    textlcdWrite(1, "  60172510 Son  ");
    textlcdWrite(2, "  60172533 Iim  ");
    sleep(2);
    
    textlcdExit();
    return 0;
}