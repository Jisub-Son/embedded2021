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

static TOUCH_MSG_T rcvMsg;
static int msgID_T;

static pthread_t touchTh_id, buttonTh_id;
static int x, y;
static int once=0;

void *touchThRcvFunc(void *args)    // rcvmsg를 쓰레드로 분리
{
  while(1){
    msgrcv(msgID_T, &rcvMsg, sizeof(rcvMsg)-sizeof(long int), 0, 0); // get touch data
    if(rcvMsg.pressed == 1) once = 1; //누르는 동작에서 once=1로 set
    x = rcvMsg.x;
    y = rcvMsg.y;
    printf("tchth rcv : %d[%d, %d, %d]\r\n", rcvMsg.pressed, x, y, once);
  }
}

void *buttonThRcvFunc(void *args)
{
  while(1){
    msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input
    if(buttonRxData.pressed == 1) once = 1; //누르는 동작에서 once=1로 set
    printf("bth rcv : %d[%d]\r\n", buttonRxData.pressed, once);
  }
}

int GameInit(void)     // 전체 init 또는 초기 필요한 Init 여기다가 모으기
{
  int i, count;

  ledLibInit();
  buttonInit();
  buzzerInit();
  fndInit();
  pwmLedInit();
  textlcdInit();
  touchInit();
	printf("Init Finish\r\n");

  //초기값 출력들 정리
  for(i=0;i<8;i++){  // led all off
		ledOnOff(i, 0);
	}
  fndOff();
  pwmLedRGB(0, 0, 0); // colorled off
  textlcdWrite(1, "                ");  //text lcd all off
  textlcdWrite(2, "                ");
  
  msgID_T = msgget (TMESSAGE_ID, IPC_CREAT|0666);
  if(msgID_T == -1){
      printf("Cannot get msgID\r\n");
      return -1;
  }
  msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
  if(msgID == -1){
      printf("Cannot get msgID\r\n");
      return -1;
  }
  // trash msg
  while(1)
  {
      int returnValue = 0;
      returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, IPC_NOWAIT); // 비었어도 리턴

      if(returnValue == -1) break;    // 비었으면 -1 리턴하기 때문
      count++;
      // printf("%d trash message Comes : [%d]\r\n", count, buttonRxData.keyInput);
  }
  printf("\tI got %d messages in the queue\r\n", count);

  printf("Init complete\r\n");
}

int GameExit(void)   // 전체 exit
{
  ledLibExit();
  buttonExit();
  buzzerExit();
  fndExit();
  pwmInactiveAll();
  textlcdExit();
  pthread_cancel(buttonTh_id);
  pthread_cancel(touchTh_id);
  printf("Exit completed!\r\n");
}

int GameTime(int game_state)   // game start 시 타이머 동작, game stop이면 타이머 끝
{
  
}

int Level1(void)   // level1(button)
{
  //home = 0, back = 1, search = 2, menu = 3, volup = 4, voldn = 5
  //pwd = 132231

  // create msg rcv thread
  pthread_create(&buttonTh_id, NULL, buttonThRcvFunc, NULL);
  pthread_create(&touchTh_id, NULL, touchThRcvFunc, NULL);    //thread 생성

  printf("level 1 start\r\n");
  print_bmp("./proj_image/ex1.bmp");  //set level1 image
  textlcdlevel(1, 1);   // set level1 txtlcd

  int index = 0;
  char pwd;
  char pwdAns[10] = {0,};
  
  while(1)
  {
    if(once == 1 && rcvMsg.pressed == 1){ // once==1이고 터치일때 if문 실행
                                 
      once = 0;                         // 바로 once=0으로 만들어서 debounce?
      if(x>0 && x<300 && y>0 && y<300){ // 그 영역이 오른쪽 상단이면
        pwmLedRGB(0, 0, 1);           // 특정 영역을 만들어서 힌트나 level 간 이동 가능하게 만들자
        printf("Give me Hint!\r\n");
      }
      else
        pwmLedRGB(0, 0, 0);
    }

    if(once == 1 && buttonRxData.pressed == 1){ // once==1이고 버튼일때 if문 실행
      once = 0;                         // 바로 once=0으로 만들어서 debounce?

      if(buttonRxData.keyInput == KEY_HOME) pwd = '0';
      if(buttonRxData.keyInput == KEY_BACK) pwd = '1';
      if(buttonRxData.keyInput == KEY_SEARCH) pwd = '2';
      if(buttonRxData.keyInput == KEY_MENU) pwd = '3';
      if(buttonRxData.keyInput == KEY_VOLUMEUP) pwd = '4';
      if(buttonRxData.keyInput == KEY_VOLUMEDOWN) pwd = '5';  // 받아온 키값을 분류하여 pwd를 정한다 if문 말고 더 깔끔한 방법은?

      switch (index)  // 인덱스에 따라(눌린 순서를 index로 구분함)
      {
        case 0: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break; //ex 첫번째 입력(index=0)일 경우 pwd(keyinput)을 pwdAns[0]에 저장
        case 1: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 2: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 3: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 4: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 5: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
      }
    }

    if(index == 6 && strcmp("132231", pwdAns) == 0) // 6번 입력했고 정답이면
    {
      printf("answer correct : %s[%d]\r\n", pwdAns, index);
      pwmLedGreen();
      textlcdWrite(2, "     Correct    ");
      buzzerifAns();
      pwmLedRGB(0, 0, 0);
      break;    // 현재는 break로 탈출 -> level2로 가게 변경해야 함
    }
    else if(index == 6 && strcmp("132231", pwdAns) != 0) // 6번 입력했고 오답이면
    {
      printf("answer wrong : %s[%d]\r\n", pwdAns, index);
      pwmLedRed();
      textlcdWrite(2, "      Wrong     ");
      buzzerifNotAns();
      sleep(1);
      textlcdWrite(2, "   Try Again    ");
      pwmLedRGB(0, 0, 0);
      index = 0;
    }else;
  }
  printf("level 1 finish\r\n");
}

int Level2(void)   // level2(buzzer)
{ 
  printf("level 2 start\r\n");
  print_bmp("./proj_image//level2/ex2.bmp");  //set level1 image
  // sleep(1);
  textlcdlevel(1, 2);   // set level2 txtlcd
  buzzerifAns();//정답일때의 부저

  int index = 0;
  char pwd;
  char pwdAns[10] = {0,};
  
  //방금 출력된 부저음을 맞추라는 이미지가 출력됨
  //이미지 안에 어떤 걸 눌러야 무슨 음이 나오는 지 알려줌
	printf("show level2 quiz.\r\n");  
	while(1)
  {
		/*
    if(once == 1 && rcvMsg.pressed == 1){ // once==1이고 터치일때 if문 실행
                                 
      once = 0;                         // 바로 once=0으로 만들어서 debounce?
      if(x>0 && x<300 && y>0 && y<300){ // 그 영역이 오른쪽 상단이면
        pwmLedRGB(0, 0, 1);           // 특정 영역을 만들어서 힌트나 level 간 이동 가능하게 만들자
        printf("Give me Hint!\r\n");
      }
      else
        pwmLedRGB(0, 0, 0);
    }
		*/

    if(once == 1 && rcvMsg.pressed == 1){ // once==1이고 버튼일때 if문 실행
      once = 0;                         // 바로 once=0으로 만들어서 debounce?

      if((x>896)&&(x<1024)&&(y>0)&&(y<500))//도
			{
				pwd = '0';
				printf("level 2 -do touched.\r\n");
        print_bmp("./proj_image/level2/do.bmp"); //도 눌린 이미지
        printf("level 2 -do bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[0], 500); //도 음의 부저 출력
        printf("level 2 -do buz.\r\n");
			}
      else if((x>768)&&(x<896)&&(y>0)&&(y<500)) //레
			{
				pwd = '1';
				printf("level 2 - re touched.\r\n");
        print_bmp("./proj_image/level2/re.bmp"); //레 눌린 이미지
        printf("level 2 - re bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[1], 500); //레 음의 부저 출력
        printf("level 2 - re buz.\r\n");
			}
      else if((x>640)&&(x<768)&&(y>0)&&(y<500)) //미
			{
				pwd = '2';
				printf("level 2 - mi touched.\r\n");
        print_bmp("./proj_image/level2/mi.bmp"); //레 눌린 이미지
        printf("level 2 - mi bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[2], 500); //레 음의 부저 출력
        printf("level 2 - mi buz.\r\n");
			}
      else if((x>512)&&(x<640)&&(y>0)&&(y<500)) //파
			{
				pwd = '3';
				printf("level 2 - fa touched.\r\n");
        print_bmp("./proj_image/level2/fa.bmp"); //레 눌린 이미지
        printf("level 2 - fa bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[3], 500); //레 음의 부저 출력
        printf("level 2 - fa buz.\r\n");
			}
      else if((x>384)&&(x<512)&&(y>0)&&(y<500)) //솔
			{
				pwd = '4';
				printf("level 2 - sol touched.\r\n");
        print_bmp("./proj_image/level2/sol.bmp"); //레 눌린 이미지
        printf("level 2 - sol bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[4], 500); //레 음의 부저 출력
        printf("level 2 - sol buz.\r\n");
			}
      else if((x>256)&&(x<384)&&(y>0)&&(y<500))  //라
			{
				pwd = '5';
				printf("level 2 - la touched.\r\n");
        print_bmp("./proj_image/level2/la.bmp"); //레 눌린 이미지
        printf("level 2 - la bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[5], 500); //레 음의 부저 출력
        printf("level 2 - la buz.\r\n");
			}
			else if((x>128)&&(x<256)&&(y>0)&&(y<500))//시
			{
				pwd = '6';
				printf("level 2 - si touched.\r\n");
        print_bmp("./proj_image/level2/si.bmp"); //레 눌린 이미지
        printf("level 2 - si bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[6], 500); //레 음의 부저 출력
        printf("level 2 - si buz.\r\n");
			}
			else if((x>0)&&(x<128)&&(y>0)&&(y<500))  //도
			{
				pwd = '7';printf("level 2 - do2 touched.\r\n");
        print_bmp("./proj_image/level2/do2.bmp"); //레 눌린 이미지
        printf("level 2 - do2 bmp.\r\n");
        buzzerPlaySongforMsec(buzzermusicScale[7], 500); //레 음의 부저 출력
        printf("level 2 - do2 buz.\r\n");
				
			}
			// 받아온 키값을 분류하여 pwd를 정한다 if문 말고 더 깔끔한 방법은?

      switch (index)  // 인덱스에 따라(눌린 순서를 index로 구분함)
      {
        case 0: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break; //ex 첫번째 입력(index=0)일 경우 pwd(keyinput)을 pwdAns[0]에 저장
        case 1: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 2: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 3: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 4: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
        case 5: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
				case 6: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
				case 7: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
      }
    }

    if(index == 4 && strcmp("0247", pwdAns) == 0) // 6번 입력했고 정답이면
    {
      printf("answer correct : %s[%d]\r\n", pwdAns, index);
      pwmLedGreen();
      textlcdWrite(2, "     Correct    ");
      buzzerifAns();
      pwmLedRGB(0, 0, 0);
      break;    // 현재는 break로 탈출 -> level2로 가게 변경해야 함
    }
    else if(index == 4 && strcmp("0247", pwdAns) != 0) // 6번 입력했고 오답이면
    {
      printf("answer wrong : %s[%d]\r\n", pwdAns, index);
      pwmLedRed();
      textlcdWrite(2, "      Wrong     ");
      buzzerifNotAns();
      sleep(1);
      textlcdWrite(2, "   Try Again    ");
      pwmLedRGB(0, 0, 0);
      index = 0;
    }else;
  }
  printf("level 2 finished\r\n");
}

int Level3(void)   // level3(colorled)
{
	//문제 도안
	//사진에서의 회색부분에 해당하는 색을 차례대로 누르면 통과 
  //home = 0, back = 1, search = 2, menu = 3, volup = 4, voldn = 5
  //pwd3 = 131

  // create msg rcv thread
  //pthread_create(&buttonTh_id, NULL, buttonThRcvFunc, NULL);
  pthread_create(&touchTh_id, NULL, touchThRcvFunc, NULL);    //thread 생성

  printf("level 3 start\r\n");
  print_bmp("./proj_image/level3/ex3.bmp");  //set level3 image
  
  textlcdlevel(1, 3);	// set level3 txtlcd

  int index3 = 0;
  char pwd3;
  char pwdAns3[10] = {0,};
  
  while(1)
  {
    if(once == 1 && rcvMsg.pressed == 1){ // once==1이고 터치일때 if문 실행
                                 
      once = 0;                         // 바로 once=0으로 만들어서 debounce?
			//341, 683
			//500, 600
      if(x>683 && x<1024 && y>0 && y<100){ // 그 영역이 하단 왼쪽이면
        pwmLedRGB(1, 0, 0);           // 빨간색 led 켜기 
        printf("Select Red!\r\n");
				print_bmp("./proj_image/level3/3_r.bmp");
      }
			else if(x>341 && x<683 && y>0 && y<100){ // 그 영역이 하단 중간부분이면 
        pwmLedRGB(1, 1, 0);           // 노란색 led 켜기 
        printf("Select Yellow!\r\n");
				print_bmp("./proj_image/level3/3_y.bmp");
      }
			else if(x>0 && x<341 && y>0 && y<100){ // 그 영역이 하단 오른쪽이면 
        pwmLedRGB(0, 1, 0);           // 초록색 led 켜기 
        printf("Select Green!\r\n");
				print_bmp("./proj_image/level3/3_g.bmp");
      }
	    
      else
        pwmLedRGB(0, 0, 0);printf("Select Nothing!\r\n");
				
    }

    //if(once == 1 && buttonRxData.pressed == 1){ // once==1이고 버튼일때 if문 실행
      //once = 0;                         // 바로 once=0으로 만들어서 debounce?

      if(x>683 && x<1024 && y>0 && y<100) pwd3 = '0'; //red
      if(x>341 && x<683 && y>0 && y<100) pwd3 = '1'; //yellow
      if(x>0 && x<341 && y>0 && y<100) pwd3 = '2'; //green
      
      switch (index3)  // 인덱스에 따라(눌린 순서를 index로 구분함)
      {
        case 0: pwdAns3[index3] = pwd3; index3++; printf("pwdAns : %s\r\n", pwdAns3); break; //ex 첫번째 입력(index=0)일 경우 pwd(keyinput)을 pwdAns[0]에 저장
        case 1: pwdAns3[index3] = pwd3; index3++; printf("pwdAns : %s\r\n", pwdAns3); break;
        case 2: pwdAns3[index3] = pwd3; index3++; printf("pwdAns : %s\r\n", pwdAns3); break;
      }
    }

    if(index3 == 3 && strcmp("010", pwdAns3) == 0) // 3번 입력했고 정답이면
    {
      printf("answer correct : %s[%d]\r\n", pwdAns3, index3);
      pwmLedGreen();
      textlcdWrite(2, "     Correct    ");
      buzzerifAns();
      pwmLedRGB(0, 0, 0);
      break;    // 현재는 break로 탈출 -> level4로 가게 변경해야 함
    }
    else if(index3 == 3 && strcmp("010", pwdAns3) != 0) // 3번 입력했고 오답이면
    {
      printf("answer wrong : %s[%d]\r\n", pwdAns3, index3);
      pwmLedRed();
      textlcdWrite(2, "      Wrong     ");
      buzzerifNotAns();
      sleep(1);
      textlcdWrite(2, "   Try Again    ");
      pwmLedRGB(0, 0, 0);
      index3 = 0;
    }else;
  }
  printf("level 3 finish\r\n");
}

int Level4(void)   // level4(temperature)
{
	//home = 0, back = 1, search = 2, menu = 3, volup = 4, voldn = 5
  //pwd = 132231

  printf("level 4 start\r\n");
  print_bmp("./proj_image/level4/notBoil.bmp");  //set level4 image

  spi_init();

	textlcdlevel(1, 4);   // set level1 txtlcd
  textlcdWrite(2, "                ");

  double test_temp;
  
  while(1)
  {

    // if(once == 1 && rcvMsg.pressed == 1){ // once==1이고 터치일때 if문 실행
                                 
    //   once = 0;                         // 바로 once=0으로 만들어서 debounce?
    //   if(x>0 && x<300 && y>0 && y<300){ // 그 영역이 오른쪽 상단이면
    //     pwmLedRGB(0, 0, 1);           // 특정 영역을 만들어서 힌트나 level 간 이동 가능하게 만들자
    //     printf("Give me Hint!\r\n");
    //   }
    //   else
    //     pwmLedRGB(0, 0, 0);
    // }
		
		test_temp = spi_read_lm74();
		printf("On test code : %lf\r\n", test_temp);
		sleep(1);

		if (test_temp>=29){
			print_bmp("./proj_image/level4/boil.bmp");
      pwmLedRGB(1, 0, 0);
      ledControl("0x7F");
      sleep(3);
      
      if(test_temp>=29){
        printf("answer correct : %lf\r\n", test_temp);
        pwmLedGreen();
        textlcdWrite(2, "     Correct    ");
        buzzerifAns();
        pwmLedRGB(0, 0, 0);
        ledControl("0x00");
        spi_exit();
        break;    // 현재는 break로 탈출 -> level4로 가게 변경해야 함
      }
    }
    else print_bmp("./proj_image/level4/notBoil.bmp");

		if(test_temp >=28 && test_temp < 29){
      pwmLedRGB(1, 1, 0);
      ledControl("0x3F");
    }
    else if(test_temp >=27 && test_temp < 28){
      pwmLedRGB(1, 1, 0);
      ledControl("0x1F");
    }
    else if(test_temp >=26 && test_temp < 27){
      pwmLedBlue();
      ledControl("0x0F");
    }
    else if(test_temp >= 25 && test_temp < 26){
      pwmLedBlue();
      ledControl("0x07");
    }
    else{
      pwmLedBlue();
      ledControl("0x03");
    }
			
			
      // pwmLedRed();
      // textlcdWrite(2, "      Wrong     ");
      // buzzerifNotAns();
      // sleep(1);
      // textlcdWrite(2, "   Try Again    ");
      // pwmLedRGB(0, 0, 0);

    
  }//while 문 종료
  
  printf("level 4 finish\r\n");
}

int Level5(void)   // level5(accel&mag)
{
	printf("level 5 start\r\n");
  print_bmp("./proj_image/level5/ex5.bmp");  //set level5 image
  
  textlcdlevel(1, 5);	// set level5 txtlcd
	
	
	MagInit();
	printf("Mag Init.\r\n");

	
	while(1)
  {
		
    int returnValue = 0;
    returnValue = msgrcv(msgID, &buttonRxData, sizeof(buttonRxData)-sizeof(long int), 0, 0);    // get button input
    printf("main button rcv : %d\r\n", buttonRxData.pressed);
		/*
		if(sensorData[1]<600 && sensorData[1]>530) pwd = '0'; //비밀번호 1
    if(sensorData[1]<530 && sensorData[1]>464) pwd = '1'; //비밀번호 2
    if(sensorData[1]<464 && sensorData[1]>398) pwd = '2'; //비밀번호 3
		if(sensorData[1]<398 && sensorData[1]>332) pwd = '3'; //비밀번호 4
		if(sensorData[1]<332 && sensorData[1]>266) pwd = '4'; //비밀번호 5
		if(sensorData[1]<266 && sensorData[1]>200) pwd = '5'; //비밀번호 6
		*/
		if(sensorData[1]<600 && sensorData[1]>530) 
		{ //자물쇠 1영역
			pwd = '0';
      printf("pwd 1!\r\n");
		  print_bmp("./proj_image/level5/5_1.bmp");
    }
		if(sensorData[1]<530 && sensorData[1]>464) 
		{ //자물쇠 2 영역
			pwd = '1';
      printf("pwd 2!\r\n");
		  print_bmp("./proj_image/level5/5_2.bmp");
    }
		if(sensorData[1]<464 && sensorData[1]>398) 
		{ //자물쇠 3 영역
			pwd = '2';
      printf("pwd 3!\r\n");
		  print_bmp("./proj_image/level5/5_3.bmp");
    }
		if(sensorData[1]<398 && sensorData[1]>332) 
		{ //자물쇠 4 영역
			pwd = '3';
      printf("pwd 4!\r\n");
		  print_bmp("./proj_image/level5/5_4.bmp");
    }
		if(sensorData[1]<332 && sensorData[1]>266) 
		{ //자물쇠 5 영역
			pwd = '4';
      printf("pwd 5!\r\n");
		  print_bmp("./proj_image/level5/5_5.bmp");
    }
		if(sensorData[1]<266 && sensorData[1]>200) 
		{ //자물쇠 6 영역
			pwd = '5';
      printf("pwd 6!\r\n");
		  print_bmp("./proj_image/level5/5_6.bmp");
    }
        
    if(buttonRxData.pressed){
			
      if (buttonRxData.keyInput == KEY_SEARCH)
      {
				
        accelMagGyroGetData(MAG);
				printf ("MAG when button pushed %d, %d, %d\r\n",sensorData[0],sensorData[1],sensorData[2]);
				
				switch (index)  // 인덱스에 따라(눌린 순서를 index로 구분함)
				{
					case 0: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break; //ex 첫번째 입력(index=0)일 경우 pwd(keyinput)을 pwdAns[0]에 저장
					case 1: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
					case 2: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
					case 3: pwdAns[index] = pwd; index++; printf("pwdAns : %s\r\n", pwdAns); break;
				}
    }

    if(index == 4 && strcmp("4102", pwdAns) == 0) // 6번 입력했고 정답이면
    {
      printf("answer correct : %s[%d]\r\n", pwdAns, index);
      pwmLedGreen();
      textlcdWrite(2, "     Correct    ");
      buzzerifAns();
      pwmLedRGB(0, 0, 0);
      break;    // 현재는 break로 탈출 -> level2로 가게 변경해야 함
    }
    else if(index == 4 && strcmp("0247", pwdAns) != 0) // 6번 입력했고 오답이면
    {
      printf("answer wrong : %s[%d]\r\n", pwdAns, index);
      pwmLedRed();
      textlcdWrite(2, "      Wrong     ");
      buzzerifNotAns();
      sleep(1);
      textlcdWrite(2, "   Try Again    ");
      pwmLedRGB(0, 0, 0);
      index = 0;
							
       }
    
        if(exit) break;
  }
}

int Level6(void)   // level6(gyro)
{}

int Level7(void)   // level7(final)
{}

int Ranking(void)  // 순위표
{}

