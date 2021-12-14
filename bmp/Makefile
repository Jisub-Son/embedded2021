CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: bitmaptest.elf touchtest

bitmaptest.elf: libMyLib.a bitmaptest.c
	$(CC) -O3 bitmaptest.c -L. -l MyLib -o bitmaptest.elf

touchtest: touchtest.c libtouch.a 
	$(CC) touchtest.c -l touch -L. -o touchtest -lpthread
# 	$(CC) -Xlinker --start-group -lpthread  -o touchtest -l touch -Xlinker --end-group -L. -lpthread

libMyLib.a: libbmp.o 
	$(AR) rc libMyLib.a libbmp.o 

libbmp.o: libbmp.h libbmp.c bitmapFileHeader.h
	$(CC) -O3 -o libbmp.o -c libbmp.c
	cp libbmp.o /home/son/embedded/embedded2021/peri/

libtouch.a: touch.o
	$(AR) rc libtouch.a touch.o

touch.o: touch.c touch.h
	$(CC) -c touch.c -o touch.o
	cp touch.o /home/son/embedded/embedded2021/peri/

clean:
	rm -f *.elf *.o *.a
	

