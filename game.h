/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Jaime Romero
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"

#include "player.h"
#include "object.h"

#define MAX_SPACES 100 /* Constant that estabilshes the maximum number of spaces as 100*/

/**
 * @brief This struct stores all the information of the game
 *
 * @author Jaime Romero
 */
typedef struct _Game {
  Player *player; /*!< Current location of the player and it information */
  Object *object; /*!< Information of the object*/
  Space *spaces[MAX_SPACES]; /*!< *an array of all the sapces of the game*/
  int n_spaces; /*!< Number of spaces that the game has */
  Command *last_cmd; /*!< It stores the last command called */
  Bool finished; /*!< It defines if the game finished or not */
} Game;

/**
 * @brief It initialices every variable of Game to default values (0, NULL, NO_ID...)
 * 
 * @author Jaime Romero
 * @param game 
 * @return OK if everything worked properly or ERROR if it didn't
 */
Status game_create(Game *game);

/**
 * @brief It destroys all the spaces and commands
 * 
 * @author Jaime Romero
 * @param game 
 * @return OK if everything worked properly or ERROR if it didn't
 */
Status game_destroy(Game *game);

/**
 * @brief It searches a certain space where an Id passed by argument is
 * 
 * @author Jaime Romero
 * 
 * @param game A pointer to the game
 * @param id The id we are looking for
 * 
 * @return A Space
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It just returns the player id (location)
 * 
 * @author Jaime Romero
 * @param game 
 * @return Id (player location)
 */
Id game_get_player_location(Game *game);

/**
 * @brief It sets the player location as the id passed as an argument
 * 
 * @author Jaime Romero
 * @param game A pointer to game 
 * @param id The Id of a player whose location will be changed
 * @return OK if everything worked properly or ERROR if it didn't
 */
Status game_set_player_location(Game *game, Id location);

/**
 * @brief It returns the the location of the object
 * 
 * @author Jaime Romero
 * @param  game A pointer to game
 * @return An id which is the location of the object
 */
Id game_get_object_location(Game *game);

/**
 * @brief It sets to the object location the id passed as an argument
 * 
 * @author Jaime Romero
 * @param game A pointer to game
 * @param id  The id of an object whose location will be changed
 * 
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_set_object_location(Game *game, Id id);

/**
 * @brief It returns the las command received
 * 
 * @author Jaime Romero
 * @param game A pointer to Game
 * @return a pointer to the structure "command"
 */
Command* game_get_last_command(Game *game);

/**
 * @brief It sets as the last command executed a command passed by argument
 * 
 * @author Jaime Romero
 * @param game A pointer to game
 * @param command The respective command which will be established as the last command used
 * @return OK if everything worked properly or ERROR if it didn't
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It says if the game is finished or not
 * 
 * @author Jaime Romero
 * @param game A pointer to game
 * @return True(1) or False(0)
 */
Bool game_get_finished(Game *game);

/**
 * @brief It sets the game to "finished" if the boolean variable gotten by the last function is 1
 * 
 * @author Jaime Romero
 * @param game A pointer to Game
 * @param finished It refers to a boolean value (1 if the game is finished 0 if not)
 * @return OK if everything worked properly or ERROR if it didn't
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief It prints all the spaces and the player and object's location 
 * 
 * @author Jaime Romero
 * @param  game A pointer to Game
 * @return VOID (Nothing)
 */
void game_print(Game *game);

#endif
