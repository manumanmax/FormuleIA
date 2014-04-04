CC=gcc
CFLAGS=-Wall -std=c99 -g

all: testPile

testPile: testPile.o pile.o
	$(CC) -o $@ $^ $(CFLAGS)

pile.o: pile.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	-rm *.o 
