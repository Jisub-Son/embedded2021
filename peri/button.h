#ifndef _BUTTON_H_
#define _BUTTON_H_

#define MESSAGE_ID 6017

typedef struct {
    long int messageNum;
    unsigned short keyInput;
    int pressed;
} BUTTON_MSG_T;

int buttonInit(void);
int buttonExit(void);

#endif