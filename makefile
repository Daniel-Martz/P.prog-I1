# Variables
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -c
OBJS = command.o space.o graphic_engine.o game_loop.o game_actions.o game.o game_reader.o object.o player.o set.o character.o
EXEC = proyecto

.PHONY: all clean
# Regla principal
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) -L. -lscreen

# Compilacion de archivos individuales
space.o: space.c space.h types.h set.h
	$(CC) $(CFLAGS) -o space.o space.c

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -o command.o command.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h set.h player.h object.h character.h libscreen.h
	$(CC) $(CFLAGS) -o graphic_engine.o graphic_engine.c

game_loop.o: game_loop.c command.h types.h game.h space.h set.h player.h object.h character.h game_actions.h graphic_engine.h game_reader.h
	$(CC) $(CFLAGS) -o game_loop.o game_loop.c

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h set.h player.h object.h character.h
	$(CC) $(CFLAGS) -o game_actions.o game_actions.c

game.o: game.c game.h command.h types.h space.h set.h player.h object.h character.h game_reader.h
	$(CC) $(CFLAGS) -o game.o game.c

game_reader.o: game_reader.c game_reader.h game.h command.h types.h space.h set.h player.h object.h character.h 
	$(CC) $(CFLAGS) -o game_reader.o game_reader.c

object.o: object.h types.h object.c 
	$(CC) $(CFLAGS) -o object.o object.c

player.o: player.h types.h player.c 
	$(CC) $(CFLAGS) -o player.o player.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -o set.o set.c

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -o character.o character.c
	
# Limpiar archivos generados
clean:
	rm -f $(EXEC) $(OBJS)

runv :
	valgrind --leak-check=full ./$(EXEC) anthill.dat




