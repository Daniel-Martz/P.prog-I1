#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "types.h"

/**
 * @brief It assigns a value from a file to every Game parameter, controling the errors
 * 
 * @author Daniel Martinez
 * @param "game and filename" the game structure and the name of the file
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_reader_create_from_file(Game *game, char *filename);

#endif
