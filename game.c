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
#include "character.h"

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
  Object *objects[MAX_OBJECTS]; /*!< Information of the objects*/
  Space *spaces[MAX_SPACES]; /*!< *an array of all the sapces of the game*/
  int n_spaces; /*!< Number of spaces that the game has */
  int n_objects; /*!< Number of objects that the game has */
  int n_characters; /*!< Number of characters that the game has */
  Command *last_cmd; /*!< It stores the last command called */
  Bool finished; /*!< It defines if the game finished or not */
  Character *characters[MAX_CHARACTERS]; /*!< It contains all the characters of the game*/
  char *message; /*!< It contains all the characters of the game*/
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
  
  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
  }
  
  for (i = 0; i < MAX_CHARACTERS; i++) {
    game->characters[i] = NULL;
  }

  game->n_spaces = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->player = player_create(INIT_ID); 
  game->last_cmd = command_create();
  game->finished = FALSE;
  game->message = NULL;

  if (!game->player || !game->last_cmd) {
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

Status game_add_object(Game *game, Object *object) {
  if ((object == NULL) || (game->n_objects >= MAX_OBJECTS)) {
    return ERROR;
  }

  game->objects[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

Status game_add_character(Game *game, Character *character) {
  if ((character == NULL) || (game->n_characters >= MAX_CHARACTERS)) {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

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

  for (i = 0; i < game->n_objects; i++) {
    object_destroy(game->objects[i]);
  }

  for (i = 0; i < game->n_characters; i++) {
    character_destroy(game->characters[i]);
  }

  command_destroy(game->last_cmd);
  player_destroy(game->player);

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

Object *game_get_object(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_objects; i++) {
    if (id == object_get_id(game->objects[i])) {
      return game->objects[i];
    }
  }

  return NULL;
}

Character *game_get_character(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_characters; i++) {
    if (id == character_get_id(game->characters[i])) {
      return game->characters[i];
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

Id game_get_player_location(Game *game) { return player_get_location (game->player); }

char *game_get_message(Game *game){
  if(!game) return NULL;

  return game->message;
}

Status game_set_message(Game *game, const char *message){
  if(!game || !message){
    return ERROR;
  }

  game->message = message;
  return OK;
}

Status game_set_player_location(Game *game, Id location) {
  if (!location) {
    return ERROR;
  }

  player_set_location(game->player, location); 

  return OK;
}

Id game_get_object_location(Game *game, Id id){
  int i;
  
  if(id == NO_ID){
    return NO_ID;
  }

  for(i=0; i<game->n_spaces; i++){
    if(space_object_is_there(game->spaces[i],id) == OK){
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

Id game_object_in_the_space(Game *game, Id space_id){
  int i;

  if(space_id == NO_ID) return NO_ID;

  for(i=0; i<game->n_objects; i++){
    if(space_id == game_get_object_location(game,object_get_id(game->objects[i]))){
      return object_get_id(game->objects[i]);
    }
  }
  return NO_ID;
}

Id game_get_character_location(Game *game, Id id){
  int i;

  for(i=0; i<game->n_spaces; i++){
    if(space_get_character(game->spaces[i]) == id){
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Status game_set_object_location(Game *game, Id space_id, Id object_id) {
  if (space_id == NO_ID || object_id == NO_ID) {
    return ERROR;
  }

  space_set_new_object(game_get_space(game, space_id),object_id);
  
  return OK;
}

Status game_set_character_location(Game *game, Id space_id, Id character_id){
  if (space_id == NO_ID || character_id == NO_ID) {
    return ERROR;
  }

  space_set_character(game_get_space(game,space_id),character_id);
  
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

Id game_get_object_from_name(Game *game, char *objname){
  int i;
  if(!objname || !game){
    return NO_ID;
  }

  for(i=0; i<game->n_objects; i++){
    if(!strcmp(object_get_name(game->objects[i]),objname)){
      return object_get_id(game->objects[i]);
    }
  }
  return NO_ID;
}

void game_print(Game *game) {
  int i = 0;


  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Objects locations:");
  for(i=0; i<game->n_objects; i++){
    printf("%d", (int)game_get_object_location(game,object_get_id(game->objects[i])));
  }
  printf("\n");

  printf("=> Characters locations:");
  for(i=0; i<game->n_characters; i++){
    printf("%d", (int)game_get_character_location(game,character_get_id(game->characters[i])));
  }
  printf("\n");

  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}

/*Declaration of the function*/
Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

