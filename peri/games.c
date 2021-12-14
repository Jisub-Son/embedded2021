#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include <dirent.h>

#include "led.h"
#include "button.h"
#include "buzzer.h"
#include "fnd.h"
#include "textlcd.h"
#include "colorled.h"
#include "temperature.h"
#include "accelMagGyro.h"
#include "../bmp/libbmp.h"
#include "../bmp/touch.h"
#include "games.h"

static BUTTON_MSG_T buttonRxData;
static int msgID;

// msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);

int GameInit(void)     // 전체 init 또는 초기 필요한 Init 여기다가 모으기
{
  // BUTTON_MSG_T buttonRxData;
  //   int msgID;
  int i;
  for (i=0;i<8;i++){  // led all off
		ledOnOff(i, 0);
	}
  fndOff();
  pwmLedRGB(0, 0, 0); // colorled off
  textlcdWrite(1, "                ");  //text lcd all off
  textlcdWrite(2, "                ");

  msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
  if(msgID == -1){
      printf("Cannot get msgID\r\n");
      return -1;
  }

  // trash msg
  int count;
  while(1)
  {
      int returnValue = 0;
      returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, IPC_NOWAIT); // 비었어도 리턴

      if(returnValue == -1) break;    // 비었으면 -1 리턴하기 때문
      count++;
      printf("%d trash message Comes : [%d]\r\n", count, buttonRxData.keyInput);
  }

printf("\tI got %d messages in the queue\r\n", count);
}

int GameExit(void)   // 전체 exit
{}

int Level1(void)   // level1(button)
{
  //home = 0, back = 1, search = 2, menu = 3, volup = 4, voldn = 5
  printf("level 1 start\r\n");
  while(1)
  {
    int returnValue = 0, pwd = 0;
    returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input
    
    if(buttonRxData.pressed == 1)
    {
      //첫번째 숫자 
      if(buttonRxData.keyInput == KEY_BACK)
      {
        //첫번째 숫자로 1을 입력했을 경우
        //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
        pwmLedGreen();//초록색 표시 
        textlcdWrite(1, "     Correct    ");
        textlcdWrite(2, " Try second No. ");
        ledOnOff(0, 1); //1번째 led on
        // ledifAns();		// All led On for 3time
        buzzerifAns();//정답일때의 부저

        //두번째 숫자를 3으로 입력했을 경우
        //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
        if(buttonRxData.keyInput == KEY_MENU)
        {    
          // ledifAns();		// All led On for 3time
          pwmLedGreen();//초록색 표시 
          textlcdWrite(1, "     Correct    ");
          textlcdWrite(2, "  Try Third No. ");
          //ledOnOff(0, 1); //0번째 led on
          ledOnOff(1, 1); //2번째 led on
          buzzerifAns();//정답일때의 부저  
          
          //세번째 숫자를 2로 입력했을 경우
          //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
          if(buttonRxData.keyInput == KEY_SEARCH)
          {
            // ledifAns();		// All led On for 3time
            pwmLedGreen();//초록색 표시 
            textlcdWrite(1, "     Correct    ");
            textlcdWrite(2, " Try Fourth No. ");
            //ledOnOff(0, 1); //1번째 led on
            //ledOnOff(1, 1); //2번째 led on
            ledOnOff(2, 1); //3번째 led on
            buzzerifAns();//정답일때의 부저
              
            // 네번째 숫자를 2로 입력했을경우 
            //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
            if(buttonRxData.keyInput == KEY_SEARCH)
            {
              // ledifAns();		// All led On for 3time
              pwmLedGreen();//초록색 표시 
              textlcdWrite(1, "     Correct    ");
              textlcdWrite(2, "  Try Fifth No. ");
              //ledOnOff(0, 1); //1번째 led on
              //ledOnOff(1, 1); //2번째 led on
              //ledOnOff(2, 1); //3번째 led on
              ledOnOff(3, 1); //4번째 led on
              buzzerifAns();//정답일때의 부저
                
              //다섯번째 숫자를 3으로 입력했을 경우
              if(buttonRxData.keyInput == KEY_MENU)
              {
                // ledifAns();		// All led On for 3time
                pwmLedGreen();//초록색 표시 
                textlcdWrite(1, "     Correct    ");
                textlcdWrite(2, "  Try Sixth No. ");
                //ledOnOff(0, 1); //1번째 led on
                //ledOnOff(1, 1); //2번째 led on
                //ledOnOff(2, 1); //3번째 led on
                //ledOnOff(3, 1); //4번째 led on
                ledOnOff(4, 1); //5번째 led on
                buzzerifAns();//정답일때의 부저
                  
                //여섯번째 숫자를 1로 입력했을 경우
                if ( buttonRxData.keyInput == KEY_HOME)
                {
                  // ledifAns();		// All led On for 3time
                  pwmLedGreen();//초록색 표시 
                  textlcdWrite(1, "     Correct    ");
                  textlcdWrite(2, "  Try Next LV.  ");
                  //ledOnOff(0, 1); //1번째 led on
                  //ledOnOff(1, 1); //2번째 led on
                  //ledOnOff(2, 1); //3번째 led on
                  //ledOnOff(3, 1); //4번째 led on
                  //ledOnOff(4, 1); //5번째 led on
                  ledOnOff(5, 1); //5번째 led on
                  buzzerifAns();//정답일때의 부저
                }
                //여섯번째 숫자를 틀렸을 경우
                else 
                {
                  //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
                  pwmLedRed(); //빨간색 표시 
                  textlcdWrite(1, "      Wrong     ");
                  textlcdWrite(2, "  Try Sixth No. ");
                  buzzerifNotAns();//오답일때의 부저
                  // break;
                }
              }  
              //다섯번째 숫자를 틀렸을 경우
              else 
              {
                //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
                pwmLedRed(); //빨간색 표시 
                textlcdWrite(1, "      Wrong     ");
                textlcdWrite(2, "  Try Fifth No. ");
                buzzerifNotAns();//오답일때의 부저
                // break;
              }
            }
            //네번째 숫자 틀렸을 경우
            else 
            {
              //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
              buzzerifNotAns();//오답일때의 부저
              pwmLedRed(); //빨간색 표시 
              textlcdWrite(1, "      Wrong     ");
              textlcdWrite(2, " Try Fourth No. ");
              break;
            }
          }
          //if wrong third no.
          else 
          {
            //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
            pwmLedRed(); //빨간색 표시 
            textlcdWrite(1, "      Wrong     ");
            textlcdWrite(2, " Try Second No. ");
            buzzerifNotAns();//오답일때의 부저
            // break;
          }
        }  
        //두번째 숫자 틀렸을 경우
        else 
        {
          //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
          pwmLedRed(); //빨간색 표시 
          textlcdWrite(1, "      Wrong     ");
          textlcdWrite(2, "  Try Third No. ");
          ledOnOff(0, 0);
          buzzerifNotAns();//오답일때의 부저
          // break;
        }
      }
      //첫번째 숫자 틀렸을 경우
      else 
      {
        //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
        pwmLedRed(); //빨간색 표시 
        textlcdWrite(1, "      Wrong     ");
        textlcdWrite(2, "   Try Again    ");
        buzzerifNotAns();//오답일때의 부저
      }
    }
  }
  printf("level 1 out\r\n");
}

int Level2(void)   // level2(buzzer)
{
  
}

int Level3(void)   // level3(colorled)
{}

int Level4(void)   // level4(temperature)
{}

int Level5(void)   // level5(accel&mag)
{}

int Level6(void)   // level6(gyro)
{}

int Level7(void)   // level7(final)
{}

int Ranking(void)  // 순위표
{}
