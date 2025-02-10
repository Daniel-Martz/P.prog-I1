/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
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
 * @author Daniel Martinez
 */
typedef struct _Game {
  Player* player_location; /*!< Current locaton of the player*/
  Object* object_location; /*!< Current location of any object*/
  Space *spaces[MAX_SPACES]; /*!< *an array of all the sapces of the game*/
  int n_spaces; /*!< Number of spaces that the game has */
  Command *last_cmd; /*!< It stores the last command called */
  Bool finished; /*!< It defines if the game finished or not */
} Game;

/**
 * @brief It initialices every vaible of a game to default values (0, NULL, NO_ID...)
 * 
 * @author Daniel Martinez
 * @param game 
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_create(Game *game);

/**
 * @brief It assigns a value from a file to every Game parameter, controling the errors
 * 
 * @author Daniel Martinez
 * @param "game and filename" the game structure and the name of the file
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief It destroies all the spaces and the commands
 * 
 * @author Daniel Martinez
 * @param game 
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_destroy(Game *game);

/**
 * @brief It search for the space from the Game that has the id passed by argument
 * 
 * @author Daniel Martinez
 * @param "game and id" a pointer to the game and the id we are looking for
 * @return A Space
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It returns the player id (location)
 * 
 * @author Daniel Martinez
 * @param game 
 * @return Id (player location)
 */
Id game_get_player_location(Game *game);

/**
 * @brief It sets to the player location the id passed as an argument
 * 
 * @author Daniel Martinez
 * @param  "game and id" a pointer to game where the player location will be changed
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief It returns the the location of the object in the game
 * 
 * @author Daniel Martinez
 * @param  game
 * @return An id that is the location of the object
 */
Id game_get_object_location(Game *game);

/**
 * @brief It sets to the object location the id passed as an argument
 * 
 * @author Daniel Martinez
 * @param  "game and id" a pointer to game where the object location will be changed
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_set_object_location(Game *game, Id id);

/**
 * @brief It returns the las command
 * 
 * @author Daniel Martinez
 * @param  game
 * @return a pointer to the structure of the command
 */
Command* game_get_last_command(Game *game);

/**
 * @brief It set to the last command of the game the command passed aas an argument
 * 
 * @author Daniel Martinez
 * @param  "game and command" a pointer to game where the object location will be changed and the respective command
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It returns is the game is finished or not
 * 
 * @author Daniel Martinez
 * @param  game 
 * @return True(1) or False(0)
 */
Bool game_get_finished(Game *game);

/**
 * @brief It establishes the game to "finished" if the boolean variable entered is 1
 * 
 * @author Daniel Martinez
 * @param  "game and finished" game refers to the Game sructure finished refers to a boolean value (1 if the game is finished 0 if not)
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief It prints all the spaces and it also prints where the player and the object are 
 * 
 * @author Daniel Martinez
 * @param  game pointer to the structure of the game
 * @return nothing
 */
void game_print(Game *game);

#endif
