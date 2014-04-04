CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g

all: testListeA

testListeA: testListeA.o listeA.o
	$(CC) -o $@ $^

testListeA.o: testListeA.c
	$(CC) -o $@ -c $^ $(CFLAGS)

listeA.o: listeA.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	-rm *.o
