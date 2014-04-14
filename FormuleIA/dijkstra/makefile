CC=gcc
LISTE = ../rechercheAlgo/Liste/
FONCTION = ../rechercheAlgo/
FILEBIN= ../TP1/bin/
FILE= ../TP1/src/
PILE=../rechercheAlgo/pile/
BIN=bin/
SRC=src/
FI=../rechercheAlgo/file/
MANUBIN=~/Bureau/GrandPrix/drivers/


CFLAGS=-Wall -std=c99 -pedantic -O3

all: MyWaywardCar

testManu: $(MANUBIN)testManu

MyWaywardCar: $(BIN)test.o $(FONCTION)fonction.o $(FILEBIN)file.o $(PILE)pile.o $(FI)fi.o
	$(CC) -o $@ $^ 

$(MANUBIN)testManu: $(BIN)test.o $(FONCTION)fonction.o $(LISTE)listeA.o $(FILEBIN)file.o $(BIN)dijkstra.o $(PILE)pile.o $(FI)fi.o
	$(CC) -o $@ $^ 

$(BIN)test.o: $(SRC)test.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(FONCTION)fonction.o: $(FONCTION)fonction.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(PILE)pile.o: $(PILE)pile.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(FI)fi.o: $(FI)file.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(FILEBIN)file.o: $(FILE)file.c
	make -C $(FILE) -O3


clean:
	-rm $(BIN)*.o
	-rm Liste/*.o
	-rm $(PILE)*.o
	-rm $(FONCTION)*.o
	-rm $(FI)*.o
