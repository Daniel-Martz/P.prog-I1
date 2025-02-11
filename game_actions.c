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
 * @brief It checks that the player is in a valid location and then change the location to the south if it is valid
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return nothing
*/
void game_actions_next(Game *game);

/**
 * @brief It checks that the player is in a valid location and then change the location to the north if it is valid
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return nothing
*/
void game_actions_back(Game *game);

/**
 * @brief It checks that the player is in a valid location and then change the location to the north if it is valid
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return nothing
*/
void game_actions_take(Game *game);

/**
 * @brief It checks that the player is in a valid location and then change the location to the north if it is valid
 * @author Daniel Martínez
 * 
 * @param game a pointer to Game
 * @return nothing
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
      game_action_take(game);
      break;
    
    case DROP:
      game_action_drop(game);
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

void game_action_take(Game *game){
    Id player_space_id = NO_ID;
    Id object_id = NO_ID;
    int i;
    Object *object;

    if(!game) return;

    player_space_id = player_get_location(game->player);
    if (player_space_id == NO_ID){
      return;
    }
    
    for(i=0;i<MAX_SPACES;i++){
      if((object_id = space_get_object(game->spaces[i]) == NO_ID)){
        if(i == MAX_SPACES){
          return;
        }
        continue;
      }
      space_set_object(game->spaces[i], NO_ID);
      break;
    }

    if(player_space_id == game->spaces[i]){
      player_set_object(game->player, object_id);
      return;
    }

    return;
}
void game_action_drop(Game *game){
    Object *player_object = NULL;
    Id player_space_id = NO_ID;

    if(!game) return;

    if(!(player_object = player_get_object(game->player))){
      return;
    }

    if((player_space_id = player_get_location(game->player)) == NO_ID){
      return;
    }

    space_set_object(game_get_space(game, player_space_id),player_object);
    player_set_object(game->player);
    
        
}


