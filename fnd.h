#ifndef __FND_DRV_H__
#define __FND_DRV_H__
#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)

typedef struct FNDWriteDataForm_tag
{
    char DataNumeric[FND_DATA_BUFF_LEN]; //숫자 0-9
    char DataDot[FND_DATA_BUFF_LEN]; //숫자 0 or 1
    char DataValid[FND_DATA_BUFF_LEN]; //숫자 0 or 1
}stFndWriteForm,*pStFndWriteForm;

int fndInit(void);                      // fnd initialize
int fndDisp(int num , int dotflag);     // 0~999999 number, dot on / off
int fndExit(void);                      // fnd Exit
int fndStaticDisp(int num);
int fndTimeDisp(void);
int fndCountDisp(int number);
int fndOff(void);

#endif// __FND_DRV_H__