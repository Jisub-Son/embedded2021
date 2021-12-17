#ifndef _GAMES_H_
#define _GAMES_H_

// 여기다가 필요한 함수들 정리해서 모으는게 좋을 듯

int GameInit(void);     // 전체 init 또는 초기 필요한 Init 여기다가 모으기
int GameExit(void);   // 전체 exit

int Level1(void);   // level1(button)
int Level2(void);   // level2(buzzer)
int Level3(void);   // level3(colorled)
int Level4(void);   // level4(temperature)
int Level5(void);   // level5(accel&mag)
int Level6(void);   // level6(gyro)
int Level7(void);   // level7(final)
int Ranking(int game_time);  // 순위표

// 기타 필요한 함수도 추가하는 걸로

#endif