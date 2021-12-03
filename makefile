CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : ledtest buttontest

buttontest : buttontest.c libMyPeri.a button.h
	$(CC) buttontest.c -l MyPeri -L. -o buttontest -lpthread

ledtest : ledtest.c libMyPeri.a led.h
	$(CC) ledtest.c -l MyPeri -L. -o ledtest

libMyPeri.a : led.o button.o
	$(AR) rc libMyPeri.a led.o button.o

led.o : led.h led.c
	$(CC) -c led.c -o led.o

button.o : button.h button.c
	$(CC) -c button.c -o button.o

clean :
	rm *.o
	rm *.a
