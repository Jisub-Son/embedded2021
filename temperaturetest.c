#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "temperature.h"

int main(int argc, char **argv)
{	
	double test_temp;

	spi_init();

	for(int i=0; i<10; i++){
		test_temp = spi_read_lm74();
		printf("On test code : %lf\r\n", test_temp);
		sleep(1);
	}
	
	spi_exit();


}
