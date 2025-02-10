#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief Carga los espacios de juego
 *  
 * @author Jaime y Dani
 * 
 * @param game Un puntero a Game
 * @param filename Un puntero al nombre del fichero
 * 
 * @return OK si todo funciona correctamente y ERROR si hay algún fallo
 */
Status game_reader_load_spaces(Game *game, char *filename);

#endif