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

BUTTON_MSG_T buttonRxData;
int msgID;

// msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);

int GameInit(void)     // 전체 init 또는 초기 필요한 Init 여기다가 모으기
{
  // BUTTON_MSG_T buttonRxData;
  //   int msgID;

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
{
  buzzerifAns();//정답일때의 부저
  sleep(1);
  //방금 출력된 부저음을 맞추라는 이미지가 출력됨
  //이미지 안에 어떤 걸 눌러야 무슨 음이 나오는 지 알려줌
  print_bmp("./proj_image/ex2.bmp"); 
   while(1)
    {
      
     
        msgrcv(msgID, &rcvMsg, sizeof(rcvMsg)-sizeof(long int), 0, 0);

        switch (rcvMsg.keyInput)
        {
        case 999:
            //printf("x : %d/t y : %d\r\n", rcvMsg.x, rcvMsg.y);
            //break;
           
            
            ///////////////////////////첫번째 음 맞추기//////////////////////////////
            if((x>0)&&(x<128)&&(y>100)&&(y<600))//도
            {
              print_bmp("./proj_image/do.bmp"); //도 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[0], 500); //도 음의 부저 출력
              
              //////////////////////////두번째 음 맞추기 /////////////////////////////
              if((x>0)&&(x<128)&&(y>100)&&(y<600))//도
              {
                print_bmp("./proj_image/do.bmp"); //도 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[0], 500); //도 음의 부저 출력
                break;
              }
              else if((x>128)&&(x<256)&&(y>100)&&(y<600))//레
              {
                print_bmp("./proj_image/re.bmp"); //레 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[1], 500); //레 음의 부저 출력
                break;
              }
              else if((x>256)&&(x<384)&&(y>100)&&(y<600))//미
              {
                print_bmp("./proj_image/mi.bmp"); //미 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[2], 500); //미 음의 부저 출력
                
                /////////////세번째 음 맞추기///////////////////////////////////////
                if((x>0)&&(x<128)&&(y>100)&&(y<600))//도
                {
                  print_bmp("./proj_image/do.bmp"); //도 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[0], 500); //도 음의 부저 출력
                  break;
                }
                else if((x>128)&&(x<256)&&(y>100)&&(y<600))//레
                {
                  print_bmp("./proj_image/re.bmp"); //레 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[1], 500); //레 음의 부저 출력
                  break;
                }
                else if((x>256)&&(x<384)&&(y>100)&&(y<600))//미
                {
                  print_bmp("./proj_image/mi.bmp"); //미 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[2], 500); //미 음의 부저 출력
                  break;
                }
                else if((x>384)&&(x<512)&&(y>100)&&(y<600))//파
                {
                  print_bmp("./proj_image/fa.bmp"); //파 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[3], 500); //파 음의 부저 출력
                  break;
                }
                else if((x>512)&&(x<640)&&(y>100)&&(y<600))//솔
                {
                  print_bmp("./proj_image/sol.bmp"); //솔 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[4], 500); //솔 음의 부저 출력
                  
                  ////////////////////////여기부터 네번째 음 맞추기/////////////////////
                  if((x>0)&&(x<128)&&(y>100)&&(y<600))//도
                  {
                    print_bmp("./proj_image/do.bmp"); //도 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[0], 500); //도 음의 부저 출력
                    break;
                  }
                  else if((x>128)&&(x<256)&&(y>100)&&(y<600))//레
                  {
                    print_bmp("./proj_image/re.bmp"); //레 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[1], 500); //레 음의 부저 출력
                    break;
                  }
                  else if((x>256)&&(x<384)&&(y>100)&&(y<600))//미
                  {
                    print_bmp("./proj_image/mi.bmp"); //미 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[2], 500); //미 음의 부저 출력
                    break;
                  }
                  else if((x>384)&&(x<512)&&(y>100)&&(y<600))//파
                  {
                    print_bmp("./proj_image/fa.bmp"); //파 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[3], 500); //파 음의 부저 출력
                    break;
                  }
                  else if((x>512)&&(x<640)&&(y>100)&&(y<600))//솔
                  {
                    print_bmp("./proj_image/sol.bmp"); //솔 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[4], 500); //솔 음의 부저 출력
                    break;
                  }
                  else if((x>640)&&(x<768)&&(y>100)&&(y<600))//라
                  {
                    print_bmp("./proj_image/la.bmp"); //라 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[5], 500); //라 음의 부저 출력
                    break;
                  }
                  else if((x>768)&&(x<896)&&(y>100)&&(y<600))//시
                  {
                    print_bmp("./proj_image/si.bmp"); //시 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[6], 500); //시 음의 부저 출력
                    break;
                  }
                  else if((x>896)&&(x<1024)&&(y>100)&&(y<600))//도
                  {
                    print_bmp("./proj_image/Do.bmp"); //높은 도 눌린 이미지
                    buzzerPlaySongforMsec(buzzermusicScale[7], 500); //도 음의 부저 출력
                    print_bmp("./proj_image/passSecond.bmp"); //두번째 레벨 통과 이미지 
                    pwmLedGreen();//초록색 표시 
                    textlcdWrite(1, "     Correct    ");
                    textlcdWrite(2, "  Try Next LV.  ");
                  }
                  break;
                  /////////////////여기까지 네번째 음 맞추기
                }
                else if((x>640)&&(x<768)&&(y>100)&&(y<600))//라
                {
                  print_bmp("./proj_image/la.bmp"); //라 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[5], 500); //라 음의 부저 출력
                  break;
                }
                else if((x>768)&&(x<896)&&(y>100)&&(y<600))//시
                {
                  print_bmp("./proj_image/si.bmp"); //시 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[6], 500); //시 음의 부저 출력
                  break;
                }
                else if((x>896)&&(x<1024)&&(y>100)&&(y<600))//도
                {
                  print_bmp("./proj_image/Do.bmp"); //높은 도 눌린 이미지
                  buzzerPlaySongforMsec(buzzermusicScale[7], 500); //도 음의 부저 출력
                  break;
                }
                break;
                ////////////////////////여기까지 세번째 음 맞추기////////////////////////
              }
              else if((x>384)&&(x<512)&&(y>100)&&(y<600))//파
              {
                print_bmp("./proj_image/fa.bmp"); //파 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[3], 500); //파 음의 부저 출력
                break;
              }
              else if((x>512)&&(x<640)&&(y>100)&&(y<600))//솔
              {
                print_bmp("./proj_image/sol.bmp"); //솔 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[4], 500); //솔 음의 부저 출력
                break;
              }
              else if((x>640)&&(x<768)&&(y>100)&&(y<600))//라
              {
                print_bmp("./proj_image/la.bmp"); //라 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[5], 500); //라 음의 부저 출력
                break;
              }
              else if((x>768)&&(x<896)&&(y>100)&&(y<600))//시
              {
                print_bmp("./proj_image/si.bmp"); //시 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[6], 500); //시 음의 부저 출력
                break;
              }
              else if((x>896)&&(x<1024)&&(y>100)&&(y<600))//도
              {
                print_bmp("./proj_image/Do.bmp"); //높은 도 눌린 이미지
                buzzerPlaySongforMsec(buzzermusicScale[7], 500); //도 음의 부저 출력
                break;
              }
              break;
              ///////////////////////여기까지 두번째 음 맞추기/////////////////////////
            }
            else if((x>128)&&(x<256)&&(y>100)&&(y<600))//레
            {
              print_bmp("./proj_image/re.bmp"); //레 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[1], 500); //레 음의 부저 출력
              break;
            }
            else if((x>256)&&(x<384)&&(y>100)&&(y<600))//미
            {
              print_bmp("./proj_image/mi.bmp"); //미 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[2], 500); //미 음의 부저 출력
              break;
            }
            else if((x>384)&&(x<512)&&(y>100)&&(y<600))//파
            {
              print_bmp("./proj_image/fa.bmp"); //파 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[3], 500); //파 음의 부저 출력
              break;
            }
            else if((x>512)&&(x<640)&&(y>100)&&(y<600))//솔
            {
              print_bmp("./proj_image/sol.bmp"); //솔 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[4], 500); //솔 음의 부저 출력
              break;
            }
            else if((x>640)&&(x<768)&&(y>100)&&(y<600))//라
            {
              print_bmp("./proj_image/la.bmp"); //라 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[5], 500); //라 음의 부저 출력
              break;
            }
            else if((x>768)&&(x<896)&&(y>100)&&(y<600))//시
            {
              print_bmp("./proj_image/si.bmp"); //시 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[6], 500); //시 음의 부저 출력
              break;
            }
            else if((x>896)&&(x<1024)&&(y>100)&&(y<600))//도
            {
              print_bmp("./proj_image/Do.bmp"); //높은 도 눌린 이미지
              buzzerPlaySongforMsec(buzzermusicScale[7], 500); //도 음의 부저 출력
              break;
            }
            pwmLedRed();//빨간색 표시 
            textlcdWrite(1, "      Wrong     ");
            textlcdWrite(2, "    Try Again   ");
            //////////////////////////여기까지 첫번째 음 맞추기///////////////////////
        
        default:
            break;
        }
    }
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
