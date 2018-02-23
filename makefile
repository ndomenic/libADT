CC = gcc
CFLAGS = -Wall -std=c11 -g

all: list lib

list: 
	$(CC) $(CFLAGS) -c src/LinkedListAPI.c -Iinclude -o bin/LinkedListAPI.o

lib:
	ar rcs bin/libADT.a bin/*.o

clean:
	rm bin/*