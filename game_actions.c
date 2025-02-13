/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

void game_actions_unknown(Game *game);

void game_actions_exit(Game *game);

/**
 * @brief It checks that the player is in a valid location and then change the location to south if it is valid
 * @author Jaime Romero
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_next(Game *game);

/**
 * @brief It checks that the player is in a valid location and then change the location to north if it is valid
 * @author Jaime Romero
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_back(Game *game);

/**
 * @brief It takes an object from a certain location
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_take(Game *game);

/**
 * @brief It drops the object previously taken
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_drop(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;
      
    case TAKE:
      game_actions_take(game);
      break;
    
    case DROP:
      game_actions_drop(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }
  return;
}

void game_actions_take(Game *game){
  Id player_location = NO_ID;
  Id object_location = NO_ID;

  if(!game) return;

  object_location = game_get_object_location(game); /* Initializate object_location*/
  if(object_location == NO_ID){
    return;
    }

  player_location = game_get_player_location(game);/* Initializate player_location*/
  if(player_location == NO_ID){
    return;
  }

  if((player_location == object_location) && (player_get_object(game->player) == NO_ID)) /* conditions needed to take an object */
  {
    player_set_object(game->player, object_get_id(game->object));/* Copy the object in the player */
    space_set_object(game_get_space(game, player_location), NO_ID);/* Delete the object from the space*/
    game_set_object_location(game, NO_ID);
    return;
  }

  return;
}
void game_actions_drop(Game *game){
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;

  if(!game) return;

  object_id = player_get_object(game->player);
  if(object_id == NO_ID) return;

  player_location = game_get_player_location(game);
  if(player_location == NO_ID){
    return;
  }

  current_space = game_get_space(game, player_location);
  if((space_get_object(current_space)== NO_ID)){
    space_set_object(current_space, object_id); /* we establish the space object id of the player's object*/
    game_set_object_location(game, player_location);
    player_set_object(game->player, NO_ID);/* we "delete" the object from the player*/
  }

  return;   
}


