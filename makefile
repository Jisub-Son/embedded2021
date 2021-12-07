CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: ledtest buttontest buzzertest fndtest textlcdtest colorledtest accelMagGyrotest temperaturetest

temperaturetest : temperaturetest.c libMyPeri.a temperature.h
	$(CC) temperaturetest.c -l MyPeri -L. -o temperaturetest

accelMagGyrotest : accelMagGyrotest.c libMyPeri.a accelMagGyro.h
	$(CC) accelMagGyrotest.c -l MyPeri -L. -o accelMagGyrotest

colorledtest : colorledtest.c libMyPeri.a colorled.h
	$(CC) colorledtest.c -l MyPeri -L. -o colorledtest

textlcdtest : textlcdtest.c libMyPeri.a textlcd.h
	$(CC) textlcdtest.c -l MyPeri -L. -o textlcdtest

fndtest : fndtest.c libMyPeri.a fnd.h
	$(CC) fndtest.c -l MyPeri -L. -o fndtest -lpthread

buzzertest : buzzertest.c libMyPeri.a buzzer.h
	$(CC) buzzertest.c -l MyPeri -L. -o buzzertest

buttontest : buttontest.c libMyPeri.a button.h
	$(CC) buttontest.c -l MyPeri -L. -o buttontest -lpthread

ledtest : ledtest.c libMyPeri.a led.h
	$(CC) ledtest.c -l MyPeri -L. -o ledtest

libMyPeri.a : led.o button.o buzzer.o fnd.o textlcd.o colorled.o accelMagGyro.o temperature.o
	$(AR) rc libMyPeri.a led.o button.o buzzer.o fnd.o textlcd.o colorled.o accelMagGyro.o temperature.o

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

colorled.o : colorled.h colorled.c
	$(CC) -c colorled.c -o colorled.o

accelMagGyro.o : accelMagGyro.h accelMagGyro.c
	$(CC) -c accelMagGyro.c -o accelMagGyro.o

temperature.o : temperature.h temperature.c
	$(CC) -c temperature.c -o temperature.o

clean :
	rm *.o
	rm *.a
