/**
 * @brief It defines the functions in charge of creating the spaces  
 * @file object.c
 * @author Jaime Romero
 * 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 */
#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "types.h"

/**
 * @brief It assigns a value from a file to every Game parameter, controling the errors
 * 
 * @author Jaime Romero
 * @param game A pointer to Game
 * @param filename A string with the name of the file
 * 
 * @return OK if everything worked correctly or ERROR if it didn't
 */
Status game_reader_create_from_file(Game *game, char *filename);

#endif
