
CC = gcc
CFLAGS = -Wall

BIN = bin/
OBJ = quadtree.o compress.o queue.o image.o menu.o button.o game.o main.o
SRC = src/
HEADERS = include/
MODULE_GRAPH = -lMLV -lm

quad: $(BIN)quadtree.o $(BIN)compress.o $(BIN)game.o $(BIN)queue.o $(BIN)image.o $(BIN)menu.o $(BIN)button.o $(BIN)main.o 
	gcc -o $@ $^ $(CFLAGS) $(MODULE_GRAPH)

$(BIN)queue.o: $(HEADERS)quadtree.h $(HEADERS)queue.h $(SRC)queue.c
	$(CC) -o $(BIN)queue.o -c $(SRC)queue.c $(CFLAGS) $(MODULE_GRAPH)

$(BIN)game.o: $(HEADERS)menu.h $(HEADERS)image.h $(HEADERS)button.h $(HEADERS)compress.h $(HEADERS)game.h $(SRC)game.c
	$(CC) -o $(BIN)game.o -c $(SRC)game.c $(CFLAGS) $(MODULE_GRAPH)

$(BIN)button.o: $(HEADERS)quadtree.h $(HEADERS)button.h $(SRC)button.c
	$(CC) -o $(BIN)button.o -c $(SRC)button.c $(CFLAGS) $(MODULE_GRAPH)

$(BIN)menu.o: $(HEADERS)quadtree.h $(HEADERS)menu.h $(SRC)menu.c
	$(CC) -o $(BIN)menu.o -c $(SRC)menu.c $(CFLAGS) $(MODULE_GRAPH)

$(BIN)image.o: $(HEADERS)quadtree.h $(HEADERS)image.h $(SRC)image.c
	$(CC) -o $(BIN)image.o -c $(SRC)image.c $(CFLAGS) $(MODULE_GRAPH)

$(BIN)compress.o: $(HEADERS)queue.h $(HEADERS)image.h $(HEADERS)compress.h $(SRC)compress.c
	$(CC) -o $(BIN)compress.o -c $(SRC)compress.c $(CFLAGS) $(MODULE_GRAPH)

$(BIN)quadtree.o: $(HEADERS)quadtree.h $(SRC)quadtree.c
	$(CC) -o $(BIN)quadtree.o -c $(SRC)quadtree.c $(CFLAGS) $(MODULE_GRAPH)

$(BIN)main.o: $(SRC)main.c $(HEADERS)game.h 
	$(CC) -o $(BIN)main.o -c $(SRC)main.c $(CFLAGS) $(MODULE_GRAPH)	


clean:
	-rm -rf $(BIN)*o
	-rm -rf $ quad
