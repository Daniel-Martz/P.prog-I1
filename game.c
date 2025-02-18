/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Jaime Romero
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_ID 1 /*Constant that refers to the starting id of a player and object */

/**
 * @brief This struct stores all the information of the game
 *
 * @author Jaime Romero
 */
struct _Game {
  Player *player; /*!< Current location of the player and it information */
  Object *object; /*!< Information of the object*/
  Space *spaces[MAX_SPACES]; /*!< *an array of all the sapces of the game*/
  int n_spaces; /*!< Number of spaces that the game has */
  Command *last_cmd; /*!< It stores the last command called */
  Bool finished; /*!< It defines if the game finished or not */
};


/**
 * @brief Determines the space where the player is
 * @author Jaime Romero
 * 
 * @param game A pointer to Game
 * @param position A number with the position
 * 
 * @return Return NO_ID if the position is negative or higher than the number of spaces available
 * if it's correct, it returns the id of the space in that position
*/
Id game_get_space_id_at(Game *game, int position);
/*Private function*/


Game *game_create(void){
  int i;
  Game *game = NULL;

  if(!(game = (Game*)calloc(1,sizeof(Game)))){
    return NULL;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player = player_create(INIT_ID); 
  game->object = object_create(INIT_ID); 
  game->last_cmd = command_create();
  game->finished = FALSE;

  if (!game->player || !game->object || !game->last_cmd) {
    return NULL;
  }

  return game;
}

Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Game *game_create_from_file(char *filename) {
  Game *game = NULL;

  if (!(game = game_create())) {
    return NULL;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    return NULL;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return game;
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

Player *game_get_player(Game *game){
  if(!game){
    return NULL;
  }
  return game->player;
}

Object *game_get_object(Game *game){
  if(!game){
    return NULL;
  }
  return game->object;
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

  for(i=0;i<game->n_spaces;i++)
  {
    if(space_get_object(game->spaces[i]) != NO_ID) return space_get_id(game->spaces[i]);
  }

  return NO_ID;
}

Status game_set_object_location(Game *game, Id id) {
  

  if (id == NO_ID) {
    return ERROR;
  }

  space_set_object(game_get_space(game, id), object_get_id(game->object));
  
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

/*Declaration of the function*/
Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

