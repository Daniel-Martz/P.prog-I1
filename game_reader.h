#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "types.h"

/**
 * @brief It reads all game parameters from a file and create the space configurated
 * @author Daniel Martínez
 * 
 * @param "game and filename" a pointer to the Game structure and a string with the filename that will be readed
 * @return OK if there was no problem, ERROR if there was any issue during the process
*/
Status game_reader_load_spaces(Game *game, char *filename);

#endif
