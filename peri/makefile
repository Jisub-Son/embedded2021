CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : project send accelMagGyrotest

project : project.c libMyPeri.a
	$(CC) project.c -l MyPeri -L. -o project -lpthread

# accelMagGyrotest : accelMagGyrotest.c libMyPeri.a accelMagGyro.h
#	$(CC) accelMagGyrotest.c -l MyPeri -L. -o accelMagGyrotest

# temperaturetest : temperaturetest.c libMyPeri.a temperature.h
# 	$(CC) temperaturetest.c -l MyPeri -L. -o temperaturetest

# colorledtest : colorledtest.c libMyPeri.a colorled.h
# 	$(CC) colorledtest.c -l MyPeri -L. -o colorledtest

# textlcdtest : textlcdtest.c libMyPeri.a textlcd.h
# 	$(CC) textlcdtest.c -l MyPeri -L. -o textlcdtest

# fndtest : fndtest.c libMyPeri.a fnd.h
# 	$(CC) fndtest.c -l MyPeri -L. -o fndtest -lpthread

# buzzertest : buzzertest.c libMyPeri.a buzzer.h
# 	$(CC) buzzertest.c -l MyPeri -L. -o buzzertest

# buttontest : buttontest.c libMyPeri.a button.h
# 	$(CC) buttontest.c -l MyPeri -L. -o buttontest -lpthread

# ledtest : ledtest.c libMyPeri.a led.h
# 	$(CC) ledtest.c -l MyPeri -L. -o ledtest

libMyPeri.a : led.o button.o buzzer.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o libbmp.o touch.o games.o
	$(AR) rc libMyPeri.a led.o button.o buzzer.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o libbmp.o touch.o games.o

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

temperature.o : temperature.h temperature.c
	$(CC) -c temperature.c -o temperature.o

accelMagGyro.o : accelMagGyro.h accelMagGyro.c
	$(CC) -c accelMagGyro.c -o accelMagGyro.o

games.o : games.h games.c
	$(CC) -c games.c -o games.o

send :
	scp project ecube@192.168.219.103:/home/ecube/
	scp Rank.txt ecube@192.168.219.103:/home/ecube/
#	scp accelMagGyrotest ecube@192.168.219.103:/home/ecube/

clean :
	rm *.o
	rm *.a
