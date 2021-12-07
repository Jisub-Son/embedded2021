#ifndef _TEXTLCD_H_
#define _TEXTLCD_H_

#define LINE_NUM			2
#define COLUMN_NUM			16	

#define  LINE_BUFF_NUM 	(COLUMN_NUM + 4)  // for dummy 
	
#define  CMD_WRITE_STRING			0x20	
	#define CMD_DATA_WRITE_BOTH_LINE	0
	#define CMD_DATA_WRITE_LINE_1		1
	#define CMD_DATA_WRITE_LINE_2		2

typedef struct TextLCD_tag 
{
	unsigned char cmd;
	unsigned char cmdData;  
	unsigned char reserved[2];
	
	char	TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;

int textlcdInit(void);      				// textlcd initialize
int textlcdWrite(int linenum, char *text);  // linenum(1~2)에 text 내용 출력하는 함수 
int textlcdTime(int linenum);				// linenum에 날짜 및 시간 출력
int textlcdlevel(int linenum, int level);	// linenum에 현재 level 표시
int textlcdExit(void); 					    // textlcd exit

#endif