#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

int spi_init(void);             // spi initialize
double spi_read_lm74(void);     // read lm74 -> 함수의 return값으로 데이터 반환한다
int spi_exit(void);             // exit

#endif
