/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Daniel Martinez
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
   Private functions
*/

/**
 * @brief It is used for unknown commands and it does nothing
 * 
 * @author Jaime Romero
 * @param game a pointer to game
 * @return Nothing
 */
void game_actions_unknown(Game *game);

/**
 * @brief It exits the game
 * 
 * @author Jaime Romero
 * @param game a pointer to game
 * @return Nothing
 */
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
 * @brief It checks that the player is in a valid location and then change the location to west if it is valid
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_left(Game *game);

/**
 * @brief It checks that the player is in a valid location and then change the location to east if it is valid
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_right(Game *game);

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
 * @brief It attacks an enemy
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_attack(Game *game);

/**
 * @brief It allows the player to chat with a friendly character
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return As a void, the function doesn't return anything
*/
void game_actions_chat(Game *game);

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
    
    case LEFT:
      game_actions_left(game);
      break;

    case RIGHT:
      game_actions_right(game);
      break;
      
    case TAKE:

      game_actions_take(game);
      break;
    
    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;

    case CHAT:
      game_actions_chat(game);
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

  game_set_message(game,NULL);

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

  game_set_message(game,NULL);

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

void game_actions_left(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  game_set_message(game, NULL);

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }
  return;
}

void game_actions_right(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  game_set_message(game,NULL);

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }
  return;
}

void game_actions_take(Game *game){
  Id player_location = NO_ID;
  Id object = NO_ID;
  Player *player = NULL;
  char *objname = NULL;

  game_set_message(game, NULL);

  if(!game) return;

  if(!(objname = command_get_objname(game_get_last_command(game)))){
    return;
  }
  /* Take the player*/
  if(!(player = game_get_player(game))) return;
  /* Make sure that the player has no objects*/
  if(player_get_object(player) != NO_ID) return;

  player_location = game_get_player_location(game);/* Initializate player_location*/
  if(player_location == NO_ID){
    return;
  }

  /* We get the object id from the name*/
  if((object = game_get_object_from_name(game, objname)) == NO_ID){
    return;
  }
  /* object location and player location must be the same*/
  if(game_get_object_location(game, object) != player_location){
    return;
  }

  player_set_object(player, object);/* Copy the object in the player */
  space_object_del(game_get_space(game, player_location), object); /*Delete the object from the sapce*/

  return;
}
void game_actions_drop(Game *game){
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;

  game_set_message(game,NULL);
  
  if(!(player = game_get_player(game))) return;

  if(!game) return;

  object_id = player_get_object(player);
  if(object_id == NO_ID) return;

  player_location = game_get_player_location(game);
  if(player_location == NO_ID){
    return;
  }

  if(!(current_space = game_get_space(game, player_location))){
    return;
  }

  space_set_new_object(current_space, object_id);
  player_set_object(player, NO_ID);
  return;   
}

void game_actions_attack(Game *game) {
  int turn = -1;
  Id character = NO_ID;
  Id player_location = NO_ID;

  game_set_message(game,NULL);
  if(!game) return;

  if((player_location = game_get_player_location(game)) == NO_ID) return;

  character = space_get_character(game_get_space(game, player_location));

  if(character == NO_ID || character_get_friendly(game_get_character(game, character)) == TRUE) return;

  /* If one of them has no health*/
  if(!((player_get_health(game_get_player(game))>0) && (character_get_health(game_get_character(game, character))>0))) return; 

  srand(time(NULL));

  turn = rand()%10;
  if((turn<0)||turn>9) return; 
  if(turn<5){
    player_set_health(game_get_player(game), player_get_health(game_get_player(game))-1);
  }
  else
    character_set_health(game_get_character(game, character),character_get_health(game_get_character(game, character))-1);
  
  if(player_get_health(game_get_player(game))<=0){
    game_set_finished(game, TRUE);
    return;
  }
}

void game_actions_chat(Game *game) {
  Id character = NO_ID;
  Id player_location = NO_ID;
  if(!game) return;

  if((player_location = game_get_player_location(game)) == NO_ID) return;

  character = space_get_character(game_get_space(game, player_location));

  if((character == NO_ID) || (character_get_friendly(game_get_character(game,character)) == FALSE)) return;
  
  game_set_message(game,character_get_message(game_get_character(game, character)));

  return;
}

