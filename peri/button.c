#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event" //실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE "/proc/bus/input/devices" //PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static pthread_t buttonTh_id;
static int fd;
static BUTTON_MSG_T buttonTxData;
static char buttonPath[200] = {0,};
int msgID;

int probeButtonPath(char *newPath) // /dev/input/event# 여기서 #에 해당하는 숫자를 확인 
{
    int returnValue = 0;
    int number = 0;

    FILE *fp = fopen(PROBE_FILE, "rt");
    while(!feof(fp) ){
        char tmpStr[200];
        fgets(tmpStr, 200, fp);
        
        if(strcmp(tmpStr, HAVE_TO_FIND_1) == 0){
            printf("YES! I found!: %s\r\n", tmpStr);
            returnValue = 1;
        }

        if( returnValue == 1 && 
            strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0){
                printf("-->%s", tmpStr);
                printf("\t%c\r\n", tmpStr[strlen(tmpStr)-3]);
                number = tmpStr[strlen(tmpStr)-3] - '0';
                break;
            }
    }

    fclose(fp);
    if(returnValue == 1)
        sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
        return returnValue;
}

void buttonThFunc(void)
{
    int readSize, inputIndex;
    struct input_event stEvent;
    
    while(1)
    {
        readSize = read(fd, &stEvent , sizeof(stEvent));
        if (readSize != sizeof(stEvent)){
            continue;
        }

        if ( stEvent.type == EV_KEY){
            buttonTxData.keyInput = stEvent.code;
            buttonTxData.pressed = stEvent.value; //1이면 버튼 눌렸을때, 0이면 버튼 떨어졌을때 
            msgsnd(msgID, &buttonTxData, sizeof(buttonTxData)-sizeof(long int), 0);
        }
    } 
}

int buttonInit(void)
{
    int err;

    if (probeButtonPath(buttonPath) == 0){
        printf("ERROR! File Not Found!\r\n");
        printf("Did you insmod?\r\n");
        return 0;
    }

    fd = open (buttonPath, O_RDONLY);

    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1){
        printf("Cannot get msgID\r\n");
        return -1;
    }
    buttonTxData.messageNum = 1;

    err = pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);
    if(err != 0){      // 만약 err이 0이 아니면(실패하면)
            printf("Thread Create Error : [%d]\r\n", err);     // 에러 메세지를 출력한다
    }
    pthread_detach(buttonTh_id);

    return 1;
}

int buttonExit(void)
{
    close(fd);

    return 1;
}
