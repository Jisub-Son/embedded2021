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

int GameInit(void)     // 전체 init 또는 초기 필요한 Init 여기다가 모으기
{}

int GameExit(void)   // 전체 exit
{}

int Level1(void)   // level1(button)
{}

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