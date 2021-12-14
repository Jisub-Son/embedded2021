CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: bitmaptest.elf
	cp *.elf ~/
clean:
	rm -f *.elf *.o *.a
	
libMyLib.a: libbmp.o 
	$(AR) rc libMyLib.a libbmp.o 

libBitmap.o: libbmp.h libbmp.c bitmapFileHeader.h
	$(CC) -O3 -o libbmp.o -c libbmp.c

bitmaptest.elf: libMyLib.a bitmaptest.c
	$(CC) -O3 bitmaptest.c -L. -l MyLib -o bitmaptest.elf
