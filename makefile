# Variables
EXE = gcc
FLAG = -Wall -pedantic -g -c
OBJ = command.o space.o graphic_engine.o game_loop.o game_actions.o game.o

# Regla principal
proyecto: $(OBJ)
	$(EXE) -o proyecto $(OBJ) -L. -lscreen

# Compilacion de archivos individuales
space.o: space.h space.c
	$(EXE) $(FLAG) -o space.o space.c

command.o: command.h command.c
	$(EXE) $(FLAG) -o command.o command.c

graphic_engine.o: graphic_engine.h types.h space.h libscreen.h graphic_engine.c
	$(EXE) $(FLAG) -o graphic_engine.o graphic_engine.c

game_loop.o: game_actions.h game.h graphic_engine.h command.h game_loop.c
	$(EXE) $(FLAG) -o game_loop.o game_loop.c

game_actions.o: game_actions.h game_actions.c
	$(EXE) $(FLAG) -o game_actions.o game_actions.c

game.o: game.h game.c
	$(EXE) $(FLAG) -o game.o game.c

# Limpiar archivos generados
clean:
	rm -f proyecto $(OBJ)



