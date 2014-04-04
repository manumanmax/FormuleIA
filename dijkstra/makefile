CC=gcc
LISTE = ../rechercheAlgo/Liste/
FONCTION = ../rechercheAlgo/
FILEBIN= ../TP1/bin/
FILE= ../TP1/src/
PILE=../rechercheAlgo/pile/
BIN=bin/
SRC=src/



CFLAGS=-Wall -std=c99 -pedantic -g -lm -pg

all: test 

test: $(BIN)test.o $(FONCTION)fonction.o $(LISTE)listeA.o $(FILEBIN)file.o $(BIN)dijkstra.o $(PILE)pile.o
	$(CC) -o $@ $^ -lm -pg

$(BIN)test.o: $(SRC)test.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)dijkstra.o: $(SRC)dijkstra.c
	$(CC) -o $@ -c $^ $(CFLAGS)
	
$(FONCTION)fonction.o: $(FONCTION)fonction.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(LISTE)listeA.o: $(LISTE)listeA.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(PILE)pile.o: $(PILE)pile.c
	$(CC) -o $@ -c $^ $(CFLAGS)


$(FILEBIN)file.o: $(FILE)file.c
	make -C $(FILE) -pg


clean:
	-rm $(BIN)*.o
	-rm Liste/*.o
	-rm $(PILE)*.o
	-rm $(FONCTION)*.o
