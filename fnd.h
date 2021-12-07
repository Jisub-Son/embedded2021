#ifndef __FND_DRV_H__
#define __FND_DRV_H__

#define MAX_FND_NUM 6 //6자리 만들어둔다 
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
#define FND_START_CNT 0
#define FND_STOP_CNT 1

typedef struct FNDWriteDataForm_tag
{
    char DataNumeric[FND_DATA_BUFF_LEN]; //숫자 0-9
    char DataDot[FND_DATA_BUFF_LEN]; //숫자 0 or 1, 점 찍을지 말지 
    char DataValid[FND_DATA_BUFF_LEN]; //숫자 0 or 1 숫자+점 전체를 켤지 끌지 
}stFndWriteForm,*pStFndWriteForm;

int fndInit(void);                      // fnd initialize
int fndDisp(int num , int dotflag);     // 0~999999 number, dot on / off
int fndExit(void);                      // fnd Exit
int fndStaticDisp(int num);             // num 출력하는 함수 
int fndTimeDisp(void);                  // 현재 시각 출력 함수
int fndCountDisp(int run);           // 1초 단위로 카운트 하는 함수
int fndOff(void);                       // fnd 끄는 함수

#endif

