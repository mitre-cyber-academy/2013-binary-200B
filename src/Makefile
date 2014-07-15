CC=gcc
CFLAGS=-c `sdl-config --cflags` -Wall -pedantic -std=c99
LIBS=`sdl-config --libs`

all: Game.bin

Game.bin: game.o
	$(CC) -o Game.bin game.o $(LIBS)

game.o: game.c
	$(CC) game.c $(CFLAGS)

clean:
	rm *.o *.bin
