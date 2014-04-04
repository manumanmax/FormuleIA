CC=gcc
LISTE = Liste/
CFLAGS=-Wall -std=c99 -pedantic -g

all: GPG

GPG: GPG.o fonction.o listeA.o
	$(CC) -o $@ $^ 

GPG.o: GPG.c
	$(CC) -o $@ -c $^ $(CFLAGS)

fonction.o: fonction.c
	$(CC) -o $@ -c $^ $(CFLAGS)

listeA.o: $(LISTE)listeA.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	-rm *.o
	-rm Liste/*.o
