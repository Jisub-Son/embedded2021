all : ledtest
	ledtest : ledtest.c libMyPeri.a led.h
	arm-linux-gnueabi-gcc ledtest.c -l MyPeri -L. -o -lpthread

libMyPeri.a : led.o
	arm-linux-gnurabi-ar rc libMyPeri.a led.o

led.o : led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

clean :
	rm *.o
	rm libMyPeri.a
