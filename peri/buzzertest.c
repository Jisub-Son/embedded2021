#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

// #define MAX_SCALE_STEP 8
// static const int buzzermusicScale[MAX_SCALE_STEP] =
// {
//     262, /*do*/ 294,330,349,392,440,494, /* si */ 523
// };

int main(void)
{
    buzzerInit();

    for(int i = 0; i < 8; i++){
        buzzerPlaySong(buzzermusicScale[i]);
        printf("scale is : %d\r\n", buzzermusicScale[i]);
        usleep(500000);
    }
    buzzerStopSong();
    printf("buzzer stop!\r\n");

    buzzerPlaySongforMsec(buzzermusicScale[0], 500);
    printf("%d scale for %d msec\r\n", buzzermusicScale[0], 500);
    buzzerPlaySongforMsec(buzzermusicScale[1], 1000);
    printf("%d scale for %d msec\r\n",buzzermusicScale[1], 1000);
    buzzerPlaySongforMsec(buzzermusicScale[2], 500);
    printf("%d scale for %d msec\r\n", buzzermusicScale[2], 500);

    usleep(500000);

    buzzerifAns();
    printf("Ans is correct!\r\n");

    usleep(500000);

    buzzerifNotAns();
    printf("Ans is Not correct!\r\n");   

    buzzerExit();
    return 0;
}