CC = gcc
CFLAGS = -g -O0

all: tp2

tp2: Main.o Graph.o Heap.o
	$(CC) $(CFLAGS) Main.o Graph.o Heap.o -o tp2.exe

Main.o: Main.c
	$(CC) $(CFLAGS) -c Main.c

Graph.o: Graph.c Graph.h
	$(CC) $(CFLAGS) -c Graph.c

Heap.o: Heap.c Heap.h
	$(CC) $(CFLAGS) -c Heap.c

clean:
	rm *.o tp2.exe
