CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar
object = led button buzzer

all: ledtest buttontest buzzertest fndtest

fndtest : fndtest.c libMyPeri.a fnd.h
	$(CC) fndtest.c -l MyPeri -L. -o fndtest

buzzertest : buzzertest.c libMyPeri.a buzzer.h
	$(CC) buzzertest.c -l MyPeri -L. -o buzzertest

buttontest : buttontest.c libMyPeri.a button.h
	$(CC) buttontest.c -l MyPeri -L. -o buttontest -lpthread

ledtest : ledtest.c libMyPeri.a led.h
	$(CC) ledtest.c -l MyPeri -L. -o ledtest

libMyPeri.a : led.o button.o buzzer.o fnd.o
	$(AR) rc libMyPeri.a led.o button.o buzzer.o fnd.o

led.o : led.h led.c
	$(CC) -c led.c -o led.o

button.o : button.h button.c
	$(CC) -c button.c -o button.o

buzzer.o : buzzer.h buzzer.c
	$(CC) -c buzzer.c -o buzzer.o

fnd.o : fnd.h fnd.c
	$(CC) -c fnd.c -o fnd.o

clean :
	rm *.o
	rm *.a
