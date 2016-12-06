CC = gcc
CFLAGS = -g -O0

all: tp1

tp1: Main.o BTree.o Serializacao.o
	$(CC) $(CFLAGS) Main.o BTree.o Serializacao.o -lm -o tp1.exe

Main.o: Main.c
	$(CC) $(CFLAGS) -c Main.c

BTree.o: BTree.c BTree.h
	$(CC) $(CFLAGS) -c BTree.c

Serializacao.o: Serializacao.c Serializacao.h
	$(CC) $(CFLAGS) -c Serializacao.c

clean:
	rm *.o tp1.exe
