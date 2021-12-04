CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: ledtest buttontest buzzertest fndtest textlcdtest

textlcdtest : textlcdtest.c libMyPeri.a textlcd.h
	$(CC) textlcdtest.c -l MyPeri -L. -o textlcdtest

fndtest : fndtest.c libMyPeri.a fnd.h
	$(CC) fndtest.c -l MyPeri -L. -o fndtest

buzzertest : buzzertest.c libMyPeri.a buzzer.h
	$(CC) buzzertest.c -l MyPeri -L. -o buzzertest

buttontest : buttontest.c libMyPeri.a button.h
	$(CC) buttontest.c -l MyPeri -L. -o buttontest -lpthread

ledtest : ledtest.c libMyPeri.a led.h
	$(CC) ledtest.c -l MyPeri -L. -o ledtest

libMyPeri.a : led.o button.o buzzer.o fnd.o textlcd.o
	$(AR) rc libMyPeri.a led.o button.o buzzer.o fnd.o textlcd.o

led.o : led.h led.c
	$(CC) -c led.c -o led.o

button.o : button.h button.c
	$(CC) -c button.c -o button.o

buzzer.o : buzzer.h buzzer.c
	$(CC) -c buzzer.c -o buzzer.o

fnd.o : fnd.h fnd.c
	$(CC) -c fnd.c -o fnd.o

textlcd.o : textlcd.h textlcd.c
	$(CC) -c textlcd.c -o textlcd.o

clean :
	rm *.o
	rm *.a
