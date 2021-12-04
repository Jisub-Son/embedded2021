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

#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

static int fd;
static stTextLCD stlcd;

int textlcdInit(void)      // textlcd initialize
{
    fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}

    return fd;
}

int textlcdWrite(int linenum, char *text)   // linenum(1~2)에 text 내용 출력하는 함수 
{   
    int len;

    if (linenum == 1){ // first line
        stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
    }
    else if ( linenum == 2){ // second line
        stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
    }
    else{
        printf("linenum : %d  wrong .  range (1 ~ 2)\n", linenum);
        return 1; 
    }
    
    printf("string : %s\n", text);
    len = strlen(text);
    
    if ( len > COLUMN_NUM ){
        memcpy(stlcd.TextData[stlcd.cmdData - 1],text,COLUMN_NUM);
    }
    else{
        memcpy(stlcd.TextData[stlcd.cmdData - 1],text,len);
    }
    stlcd.cmd = CMD_WRITE_STRING;
    
	write(fd,&stlcd,sizeof(stTextLCD));
    return 0;
}

int textlcdExit(void)      // textlcd exit
{       
    memset(&stlcd,0,sizeof(stTextLCD));
    close(fd);

    return 0;
}