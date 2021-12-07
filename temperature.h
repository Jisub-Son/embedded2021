#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

int spi_init(void);
double spi_read_lm74(void);
int spi_exit(void);

#endif
