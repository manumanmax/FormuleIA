CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -I ../include -g
BIN=../bin/

all: test

test: $(BIN)test.o $(BIN)file.o
	$(CC) -o $@ $^

$(BIN)test.o: test.c
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BIN)file.o: file.c
	$(CC) -c $^ -o $@ $(CFLAGS)

clean: 
	-rm $(BIN)*.o
