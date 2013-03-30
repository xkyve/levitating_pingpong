CC=gcc
CFLAGS=-c -Wall

all: fuzzy-proj

fuzzy-proj: main.o fuzzy.o
	$(CC) main.o fuzzy.o -o fuzzy-proj

main.o: main.c
	$(CC) $(CFLAGS) main.c

fuzzy.o: fuzzy.c
	$(CC) $(CFLAGS) fuzzy.c

clean:
	rm -rf *.o
	rm -rf *.exe
