/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/


/**
 * @brief It adds a new space to the game
 * @author Daniel Martínez
 * 
 * @param "game and space" A pointer to the Game information and a pointer to Space struct
 * @return OK if everything went good, ERROR if not
*/
Status game_add_space(Game *game, Space *space);

/**
 * @brief Determines the space where the player is
 * @author Daniel Martínez
 * 
 * @param "game and position" A pointer to the Game information and a number with the position
 * @return Return NO_ID if the position is negative or higher than the number of spaces that there are
 * if its correct it return the space for that position
*/
Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/
  
Status game_create(Game *game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player = player_create(1); 
  game->object = object_create(1); 
  game->last_cmd = command_create();
  game->finished = FALSE;

  if (!game->player || !game->object || !game->last_cmd) {
    return ERROR;
  }

  return OK;
}

Status game_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game,0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  if (!game) return ERROR;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  command_destroy(game->last_cmd);
  player_destroy(game->player);
  object_destroy(game->object);

  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) { return player_get_location (game->player); }

Status game_set_player_location(Game *game, Id location) {
  if (!location) {
    return ERROR;
  }

  player_set_location(game->player, location); 

  return OK;
}

Id game_get_object_location(Game *game){
  int i;

  for(i=0;i<MAX_SPACES;i++)
  {
    if(space_get_object(game->spaces[i])) return space_get_id(game->spaces[i]);
  }

  return NO_ID;
}

Status game_set_object_location(Game *game, Id id) {
  

  if (id == NO_ID) {
    return ERROR;
  }

  space_set_object(game_get_space(game, id), game->object);
  
  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game_get_object_location(game));
  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}

/**
   Implementation of private functions
*/


Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}
