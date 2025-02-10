# Variables
CC = gcc
FLAG = -Wall -pedantic -g -c
OBJ = command.o space.o graphic_engine.o game_loop.o game_actions.o game.o game_reader.o object.o player.o

# Regla principal
proyecto: $(OBJ)
	$(CC) -o proyecto $(OBJ) -L. -lscreen

# Compilacion de archivos individuales
space.o: space.h space.c
	$(CC) $(FLAG) -o space.o space.c

command.o: command.h command.c
	$(CC) $(FLAG) -o command.o command.c

graphic_engine.o: graphic_engine.h types.h space.h libscreen.h graphic_engine.c
	$(CC) $(FLAG) -o graphic_engine.o graphic_engine.c

game_loop.o: game_actions.h game.h graphic_engine.h command.h game_loop.c
	$(CC) $(FLAG) -o game_loop.o game_loop.c

game_actions.o: game_actions.h game_actions.c
	$(CC) $(FLAG) -o game_actions.o game_actions.c

game.o: game.h game.c
	$(CC) $(FLAG) -o game.o game.c

game_reader.o: game_reader.h game_reader.c 
	$(CC) $(FLAG) -o game_reader.o game_reader.c

object.o: object.h object.c 
	$(CC) $(FLAG) -o object.o object.c

player.o: player.h player.c 
	$(CC) $(FLAG) -o player.o player.c

# Limpiar archivos generados
clean:
	rm -f proyecto $(OBJ)



