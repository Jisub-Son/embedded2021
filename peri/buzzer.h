#ifndef _BUZZER_H_
#define _BUZZER_H_

#define MAX_SCALE_STEP 8

static const int buzzermusicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

int buzzerInit(void);           // buzzer 초기화 함수
int buzzerPlaySong(int scale);  // scale 음계를 울리는 함수
int buzzerStopSong(void);       // 소리 끄는 함수
int buzzerPlaySongforMsec(int scale, int msec);   // scale 음계를 msec 동안만 울리는 함수
int buzzerifAns(void);          // 정답일 때 울리는 함수
int buzzerifNotAns(void);       // 틀렸을 때 울리는 함수
int buzzerExit(void);           // buzzer exit

#endif