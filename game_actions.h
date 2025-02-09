/**
 * @brief It defines the game update interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
 * @brief First of all it establishes the command passed as an argument as the last command of the game
 * then it does an action depending on the command:
 *  UNKNOWN: ??
 *  EXIT: ??
 *  NEXT: Moves to the north
 *  BACK: Moves to the south
 * @author Daniel Martínez
 * 
 * @param (game and cmd) pointers to the Game structure and to the command that contains the action
 * @return OK if everything was correct, ERROR if not
*/
Status game_actions_update(Game *game, Command *cmd);

#endif
