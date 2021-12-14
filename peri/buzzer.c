#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"


#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
#define MAX_SCALE_STEP 8

// static const int musicScale[MAX_SCALE_STEP] =
// {
//     262, /*do*/ 294,330,349,392,440,494, /* si */ 523
// };
static char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨
static int fd_en, fd_freq;
static char path_en[200] = {0,}, path_freq[200] = {0,};

int findBuzzerSysPath(char *gBuzzerBaseSysDir)     //버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것
{
    DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH); //path에 가서 
    int ifNotFound = 1;
    if (dir_info != NULL){
        while (1){
            struct dirent *dir_entry;//안에 있는 모든 파일을 읽고 
            dir_entry = readdir (dir_info);
            if (dir_entry == NULL) break;
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0){ //peribuzzer에 해당하는 파일 이름이 있는지 검사해서 
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name); //있으면 파일 이름 찾아내기 
            }
        }
    }
    printf("find %s\n",gBuzzerBaseSysDir);
    return ifNotFound;
}

int buzzerInit(void)           // buzzer 초기화 함수
{    
    if (findBuzzerSysPath(gBuzzerBaseSysDir) == 1){
        printf("ERROR! File Not Found!\r\n");
        printf("Did you insmod?\r\n");
        return 0;
    }
    sprintf(path_en, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    sprintf(path_freq, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);

    fd_en = open (path_en, O_WRONLY);
    fd_freq = open (path_freq, O_WRONLY);

    return 1;
}

int buzzerPlaySong(int scale)  // scale 음계를 울리는 함수
{
    dprintf(fd_freq, "%d", scale);
    write(fd_en, &"1", 1);
    
    return 1;
}

int buzzerStopSong(void)       // 소리 끄는 함수
{
    write(fd_en, &"0", 1);

    return 1;
}

int buzzerPlaySongforMsec(int scale, int msec)   // scale 음계를 msec 동안만 울리는 함수
{
    buzzerPlaySong(scale);
    usleep(1000 * msec);
    buzzerStopSong();
}

int buzzerifAns(void)          // 정답일 때 울리는 함수
{
    buzzerPlaySongforMsec(musicScale[0], 200);
    buzzerPlaySongforMsec(musicScale[2], 200);
    buzzerPlaySongforMsec(musicScale[4], 200);
    buzzerPlaySongforMsec(musicScale[7], 400);
}

int buzzerifNotAns(void)       // 틀렸을 때 울리는 함수
{
    buzzerPlaySongforMsec(musicScale[0], 100);
    usleep(200);
    buzzerPlaySongforMsec(musicScale[0], 100);
}

int buzzerExit(void)           // buzzer exit
{
    buzzerStopSong();
    close(fd_freq);
    close(fd_en);
    return 0;
}
