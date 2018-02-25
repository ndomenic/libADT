CC = gcc
CFLAGS = -Wall -std=c11 -g

all: list hTable lib

list: 
	$(CC) $(CFLAGS) -c src/LinkedListAPI.c -Iinclude -o bin/LinkedListAPI.o

hTable: 
	$(CC) $(CFLAGS) -c src/HashTableAPI.c -Iinclude -o bin/HashTableAPI.o

lib:
	ar rcs bin/libADT.a bin/*.o

clean:
	rm bin/*