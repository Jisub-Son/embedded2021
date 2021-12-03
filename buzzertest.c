#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 8
static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

int main(void)
{
    buzzerInit();

    for(int i = 0; i < 8; i++){
        buzzerPlaySong(musicScale[i]);
        printf("scale is : %d\r\n", musicScale[i]);
        usleep(500000);
    }
    buzzerStopSong();
    printf("buzzer stop!\r\n");

    buzzerPlaySongforMsec(musicScale[0], 500);
    printf("%d scale for %d msec\r\n", musicScale[0], 500);
    buzzerPlaySongforMsec(musicScale[1], 1000);
    printf("%d scale for %d msec\r\n", musicScale[1], 1000);
    buzzerPlaySongforMsec(musicScale[2], 500);
    printf("%d scale for %d msec\r\n", musicScale[2], 500);

    usleep(500000);

    buzzerifAns();
    printf("Ans is correct!\r\n");

    usleep(500000);

    buzzerifNotAns();
    printf("Ans is Not correct!\r\n");   

    buzzerExit();
    return 0;
}