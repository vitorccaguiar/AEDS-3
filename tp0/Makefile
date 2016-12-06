CC = gcc
CFLAGS = -g -O0

all: compress

compress: Main.o Arquivo.o LZ77.o KMP.o VetorSaida.o
	$(CC) $(CFLAGS) Main.o Arquivo.o LZ77.o KMP.o VetorSaida.o -o compress.exe

Main.o: Main.c
	$(CC) $(CFLAGS) -c Main.c

Arquivo.o: Arquivo.c Arquivo.h
	$(CC) $(CFLAGS) -c Arquivo.c

LZ77.o: LZ77.c LZ77.h
	$(CC) $(CFLAGS) -c LZ77.c

KMP.o: KMP.c KMP.h
	$(CC) $(CFLAGS) -c KMP.c

VetorSaida.o: VetorSaida.c VetorSaida.h
	$(CC) $(CFLAGS) -c VetorSaida.c	

clean:
	rm *.o compress.exe
