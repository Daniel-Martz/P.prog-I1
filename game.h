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
#include "character.h"

#define MAX_SPACES 100 /* Constant that estabilshes the maximum number of spaces as 100*/
#define MAX_OBJECTS 100 /* Constant that estabilshes the maximum number of objects as 100*/
#define MAX_CHARACTERS 100 /* Constant that estabilshes the maximum number of characters as 100*/

typedef struct _Game Game;

/**
 * @brief It initialices every variable of Game to default values (0, NULL, NO_ID...)
 * 
 * @author Jaime Romero
 * @param game 
 * @return OK if everything worked properly or ERROR if it didn't
 */
Game *game_create(void);

/**
 * @brief It adds a new space to the game
 * @author Jaime Romero
 * 
 * @param game A pointer to Game
 * @param space A pointer to Space
 * 
 * @return OK if everything went good, ERROR if not
*/
Status game_add_space(Game *game, Space *space);

/**
 * @brief It adds a new object to the game
 * @author Daniel Martínez
 * 
 * @param game A pointer to Game
 * @param object A pointer to Object
 * 
 * @return OK if everything went good, ERROR if not
*/
Status game_add_object(Game *game, Object *object);

/**
 * @brief It adds a new character to the game
 * @author Daniel Martínez
 * 
 * @param game A pointer to Game
 * @param character A pointer to Character
 * 
 * @return OK if everything went good, ERROR if not
*/
Status game_add_character(Game *game, Character *character);

/**
 * @brief It assigns a value from a file to every Game parameter, controling the errors
 * 
 * @author Daniel Martínez
 * @param game A pointer to Game
 * @param filename A string with the name of the file
 * 
 * @return OK if everything worked correctly or ERROR if it didn't
 */
Game *game_create_from_file(char *filename);

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
 * @brief It looks for an object
 * 
 * @author Daniel Martínez
 * 
 * @param game A pointer to the game
 * @param id The id of the object
 * 
 * @return An Object
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief It looks for a character
 * 
 * @author Daniel Martínez
 * 
 * @param game A pointer to the game
 * @param id The id of the character
 * 
 * @return A Character
 */
Character *game_get_character(Game *game, Id id);

/**
 * @brief It searches for the player of the game
 * 
 * @author Daniel Martínez
 * 
 * @param game A pointer to the game
 * 
 * @return A Player
 */
Player *game_get_player(Game *game);


/**
 * @brief It just returns the id of the space where the player is
 * 
 * @author Jaime Romero
 * @param game A pointer to the game
 * @return Id (player location)
 */
Id game_get_player_location(Game *game);

/**
 * @brief It just returns the id of the space where an object is
 * 
 * @author Daniel Martínez
 * @param game A pointer to the game
 * @param id The id of the object which location are searching
 * @return Id (object location)
 */
Id game_get_object_location(Game *game, Id id);

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
 * @brief It just returns the id of the space where a character is
 * 
 * @author Daniel Martínez
 * @param game A pointer to the game
 * @param id The id of the character which location are searching
 * @return Id (character location)
 */
Id game_get_character_location(Game *game, Id id);

/**
 * @brief It sets to an object a location
 * 
 * @author Daniel Martínez
 * @param game A pointer to game
 * @param object_id  The id of the object whose location will be setted
 * @param space_id  The id of the location
 * 
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_set_object_location(Game *game, Id space_id, Id object_id);

/**
 * @brief It sets to a character a location
 * 
 * @author Daniel Martínez
 * @param game A pointer to game
 * @param character_id  The id of the character whose location will be setted
 * @param space_id  The id of the location
 * 
 * @return OK if everything was good, or ERROR if there was any issue
 */
Status game_set_character_location(Game *game, Id space_id, Id character_id);

/**
 * @brief It returns the las command received
 * 
 * @author Jaime Romero
 * @param game A pointer to Game
 * @return a pointer to the structure "command"
 */
Command* game_get_last_command(Game *game);

/**
 * @brief It gets the id of the object which name is passed by argument
 * 
 * @author Daniel Martínez
 * @param game A pointer to game
 * @param objname The name of the object
 * @return NO_ID if there was a problem, or the id of the object if everyithing was OK.
 */
Id game_get_object_from_name(Game *game, char *objname);

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
 * @brief This function is used to get the object of a certain space which id is passed by argument
 * 
 * @author Daniel Martínez
 * @param game A pointer to Game
 * @param space_id Id of the space 
 * @return NO_ID if there is no object in the space, or the Id of the object if it is there
 */
Id game_object_in_the_space(Game *game, Id space_id);

/**
 * @brief It prints all the spaces and the player and object's location 
 * 
 * @author Jaime Romero
 * @param  game A pointer to Game
 * @return VOID (Nothing)
 */
void game_print(Game *game);

/**
 * @brief It sets the message the character is going to say
 * 
 * @author Daniel Martinez
 * @param game A pointer to game
 * @param message A pointer to the message
 * @return True(1) or False(0)
 */
Status game_set_message(Game *game, const char *message);

/**
 * @brief It reads the message the character says
 * 
 * @author Daniel Martinez
 * @param game A pointer to game
 * @return a char with the message
 */
char *game_get_message(Game *game);

#endif
