CC = gcc
CFLAGS = -lm -O0

all: tp3

tp3: Main.o Algorithms.o
	$(CC) $(CFLAGS) Main.o Algorithms.o -o tp3.exe

Main.o: Main.c
	$(CC) $(CFLAGS) -c Main.c

Algorithms.o: Algorithms.c Algorithms.h
	$(CC) $(CFLAGS) -c Algorithms.c

clean:
	rm *.o tp3.exe
