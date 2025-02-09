/**
 * @file player.h
 * @author Daniel Martinez
 * @brief It defines the Player module interface
 * @version 0.1
 * @date 2025-02-08
 * @copyright Copyright (c) 2025
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "space.h"
#include "object.h"

typedef struct Player_ Player;
/**
 * @brief It creates a new player, allocating the necessary memory and initializating its memebers
 * @author Daniel Martínez
 *
 * @param  id the identification number for the new player
 * @return a new player, initialized
 */
Player* player_create(Id id, const char* name);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Daniel Martínez
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroys(Player* player);

/**
 * @brief It gets the id of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the id of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @param id the id that we want to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_id(Player* player, Id id);

/**
 * @brief It gets the name of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @return the name of player
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the name of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the location of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @return the location of the player
 */
Space* player_get_location(Player* player);

/**
 * @brief It sets the location of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @param name a pointer to the space that we want to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location(Player* player, Space* space);

/**
 * @brief It gets the object of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @return the object of the player
 */
Object* player_get_object(Player* player);

/**
 * @brief It sets the object of a player
 * @author Daniel Martínez
 *
 * @param player a pointer to the player
 * @param name a pointer to the object to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player* player, Object* object);

/**
 * @brief It prints the player information
 * @author Daniel Martínez
 *
 * This fucntion shows the id and name of the player, the space where the player is and wheter he has an object or not.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);

#endif 