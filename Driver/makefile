CC=gcc
BIN=bin/
SRC=src/
MANUBIN=~/Bureau/GrandPrix/drivers/


CFLAGS=-Wall -std=c99 -pedantic -O3

all: MyWaywardCar

testManu: $(MANUBIN)testManu

MyWaywardCar: $(BIN)test.o $(BIN)fonction.o $(BIN)pile.o $(BIN)fi.o
	$(CC) -o $@ $^ 

$(MANUBIN)testManu: $(BIN)test.o $(BIN)pile.o $(BIN)fi.o $(BIN)fonction.o
	$(CC) -o $@ $^ 

$(BIN)test.o: $(SRC)test.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)fonction.o: $(SRC)fonction.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)pile.o: $(SRC)pile.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)fi.o: $(SRC)file.c
	$(CC) -o $@ -c $^ $(CFLAGS)


clean:
	-rm $(BIN)*.o
	
