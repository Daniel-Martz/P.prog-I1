# Variables
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -c
OBJS = command.o space.o graphic_engine.o game_loop.o game_actions.o game.o game_reader.o object.o player.o

# Regla principal
all: proyecto

proyecto: $(OBJS)
	$(CC) -o proyecto $(OBJS) -L. -lscreen

# Compilacion de archivos individuales
space.o: space.h types.h object.h space.c
	$(CC) $(CFLAGS) -o space.o space.c

command.o: command.h types.h command.c
	$(CC) $(CFLAGS) -o command.o command.c

graphic_engine.o: graphic_engine.h game.h types.h space.h libscreen.h graphic_engine.c
	$(CC) $(CFLAGS) -o graphic_engine.o graphic_engine.c

game_loop.o: game_actions.h game.h graphic_engine.h command.h game_loop.c
	$(CC) $(CFLAGS) -o game_loop.o game_loop.c

game_actions.o: game_actions.h game_actions.c
	$(CC) $(CFLAGS) -o game_actions.o game_actions.c

game.o: game.h command.h space.h types.h player.h object.h game_reader.h game.c
	$(CC) $(CFLAGS) -o game.o game.c

game_reader.o: game_reader.h game.h game_reader.c 
	$(CC) $(CFLAGS) -o game_reader.o game_reader.c

object.o: object.h types.h object.c 
	$(CC) $(CFLAGS) -o object.o object.c

player.o: player.h types.h player.c 
	$(CC) $(CFLAGS) -o player.o player.c

# Limpiar archivos generados
clean:
	rm -f proyecto $(OBJS)




