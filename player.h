/**
 * @brief It defines the player module
 * @file player.h
 * @author Jaime Romero
 * 
 * @version 0.1
 * @date 2025-02-7
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

/**
 * @brief Creates a new player from a certain Id given
 * @author Jaime Romero
 *
 * @param id Player identifier
 * 
 * @return A new player, initiaized
 */
Player* player_create (Id id);

/**
 * @brief it destroys a player, freeing the allocated memory for it
 * @author Jaime Romero
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy (Player* player);

/**
 * @brief It gets the id of the player
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return the id of the player
 */
Id player_get_id (Player* player);

/**
 * @brief It gets the object the player is carrying
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return the object that the player is carrying
 */
Id player_get_object (Player* player);

/**
 * @brief Gets the player's name
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return a string with the name of the player
 */
const char* player_get_name (Player* player);

/**
 * @brief It gets the player's location
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return the location of the player
 */
Id player_get_location (Player* player);

/**
 * @brief Assigns an id to a player
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_id (Player* player, Id id);

/**
 * @brief Assigns a name to a player
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name (Player* player, const char* name);

/**
 * @brief Changes the object a player is carrying
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object (Player* player, Id object);

/**
 * @brief Changes the player's location
 * @author Jaime Romero
 *
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location (Player* player, Id location);

/**
 * @brief Prints the player's information
 * The function displays the player's Id, location, object and name
 * @author Jaime Romero
 * 
 * @param player A pointer to the player
 * @return OK if everything goes well, ERROR if there is any failure
 */
Status player_print (Player* player);

#endif
