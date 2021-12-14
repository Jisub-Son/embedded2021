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
#include "games.h"

BUTTON_MSG_T buttonRxData;
int msgID;

msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);

int GameInit(void)     // 전체 init 또는 초기 필요한 Init 여기다가 모으기
{}

int GameExit(void)   // 전체 exit
{}

int Level1(void)   // level1(button)
{
//home = 0, back = 1, search = 2, menu = 3, volup = 4, voldn = 5
  while(1)
  {
    int returnValue = 0;
    returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input
    
    //첫번째 숫자 
    if ( buttonRxData.keyInput == KEY_BACK)
    {
      //첫번째 숫자로 1을 입력했을 경우
      //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
      if(buttonRxData.pressed)//첫번째 숫자로 1을 입력했을 경우
      {
        ledifAns();		// All led On for 3time
        buzzerifAns();//정답일때의 부저
        pwmLedGreen();//초록색 표시 
        textlcdWrite(1, "     Correct    ");
        textlcdWrite(2, " Try second No. ");
        ledOnOff(0, 1); //1번째 led on
        
        //두번째 숫자를 3으로 입력했을 경우
        //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
        if ( buttonRxData.keyInput == KEY_MENU)
        {
          //이 코드르 원래 넣었어야하는데.. 까먹어 버려서 일단 뺌..
          //if(buttonRxData.pressed)
          //{
            
          ledifAns();		// All led On for 3time
          buzzerifAns();//정답일때의 부저
          pwmLedGreen();//초록색 표시 
          textlcdWrite(1, "     Correct    ");
          textlcdWrite(2, "  Try Third No. ");
          //ledOnOff(0, 1); //0번째 led on
          ledOnOff(1, 1); //2번째 led on
          
          //세번째 숫자를 2로 입력했을 경우
          //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
          if ( buttonRxData.keyInput == KEY_SEARCH)
          {
            ledifAns();		// All led On for 3time
            buzzerifAns();//정답일때의 부저
            pwmLedGreen();//초록색 표시 
            textlcdWrite(1, "     Correct    ");
            textlcdWrite(2, " Try Fourth No. ");
            //ledOnOff(0, 1); //1번째 led on
            //ledOnOff(1, 1); //2번째 led on
            ledOnOff(2, 1); //3번째 led on
            
            //네번째 숫자를 2로 입력했을경우 
            //맞았다는 부저 울리고 txt lcd에는 다음숫자를 맞추라는 표시, led 하나 켜기 컬러 led에 초록색불  
            if ( buttonRxData.keyInput == KEY_SEARCH)
            {
              ledifAns();		// All led On for 3time
              buzzerifAns();//정답일때의 부저
              pwmLedGreen();//초록색 표시 
              textlcdWrite(1, "     Correct    ");
              textlcdWrite(2, "  Try Fifth No. ");
              //ledOnOff(0, 1); //1번째 led on
              //ledOnOff(1, 1); //2번째 led on
              //ledOnOff(2, 1); //3번째 led on
              ledOnOff(3, 1); //4번째 led on
              
              //다섯번째 숫자를 3으로 입력했을 경우
              if ( buttonRxData.keyInput == KEY_MENU)
              {
                ledifAns();		// All led On for 3time
                buzzerifAns();//정답일때의 부저
                pwmLedGreen();//초록색 표시 
                textlcdWrite(1, "     Correct    ");
                textlcdWrite(2, "  Try Sixth No. ");
                //ledOnOff(0, 1); //1번째 led on
                //ledOnOff(1, 1); //2번째 led on
                //ledOnOff(2, 1); //3번째 led on
                //ledOnOff(3, 1); //4번째 led on
                ledOnOff(4, 1); //5번째 led on
                
                //여섯번째 숫자를 1로 입력했을 경우
                if ( buttonRxData.keyInput == KEY_HOME)
                {
                  ledifAns();		// All led On for 3time
                  buzzerifAns();//정답일때의 부저
                  pwmLedGreen();//초록색 표시 
                  textlcdWrite(1, "     Correct    ");
                  textlcdWrite(2, "  Try Next LV.  ");
                  //ledOnOff(0, 1); //1번째 led on
                  //ledOnOff(1, 1); //2번째 led on
                  //ledOnOff(2, 1); //3번째 led on
                  //ledOnOff(3, 1); //4번째 led on
                  //ledOnOff(4, 1); //5번째 led on
                  ledOnOff(5, 1); //5번째 led on

                }

                //여섯번째 숫자를 틀렸을 경우
                else 
                {
                  //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
                  buzzerifNotAns();//오답일때의 부저
                  pwmLedRed(); //빨간색 표시 
                  textlcdWrite(1, "      Wrong     ");
                  textlcdWrite(2, "  Try Sixth No. ");
                  break;
                }
              }
              
              //다섯번째 숫자를 틀렸을 경우
              else 
              {
                //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
                buzzerifNotAns();//오답일때의 부저
                pwmLedRed(); //빨간색 표시 
                textlcdWrite(1, "      Wrong     ");
                textlcdWrite(2, "  Try Fifth No. ");
                break;
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
            buzzerifNotAns();//오답일때의 부저
            pwmLedRed(); //빨간색 표시 
            textlcdWrite(1, "      Wrong     ");
            textlcdWrite(2, " Try Second No. ");
            break;
          }

        }
        
        //두번째 숫자 틀렸을 경우
        else 
        {
          //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
          buzzerifNotAns();//오답일때의 부저
          pwmLedRed(); //빨간색 표시 
          textlcdWrite(1, "      Wrong     ");
          textlcdWrite(2, "  Try Third No. ");
          break;
        }
       
      }
    }
    //첫번째 숫자 틀렸을 경우
    else 
    {
      //틀렸다는 표시로 부저 한번 울리고, led하나 끄기, 컬러led 빨간불
      buzzerifNotAns();//오답일때의 부저
      pwmLedRed(); //빨간색 표시 
      textlcdWrite(1, "      Wrong     ");
      textlcdWrite(2, "   Try Again    ");
      break;
    }
  }
}

int Level2(void)   // level2(buzzer)
{}

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
