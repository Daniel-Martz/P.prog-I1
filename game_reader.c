/**
 * @brief It creates and adds the spaces 
 * @file game_reader.c
 * @author Jaime Romero
 * 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 */
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;
  char gdesc[N_ROWS][N_COLUMNS];
  int row=0;

  if (!filename || !game) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);

      for (row = 0; row < N_ROWS; row++)
      {
        toks=strtok(NULL, "|");
        strncpy(gdesc[row], toks, N_COLUMNS-1);
        gdesc[row][N_COLUMNS-1]= '\0';
      }

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_gdesc(space, gdesc);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status game_reader_load_objects(Game *game, char *filename){

  FILE *file=NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id object_id = NO_ID, space_id = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename || !game) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)){
    if (strncmp("#o:", line, 3) == 0){
      /*Read all the data and then store it in variables*/
      toks = strtok(line + 3, "|");
      object_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      space_id = atol(toks);
      
      /*Create the object*/
      object = object_create(object_id);
      if (!object) return ERROR;
      object_set_name(object, name);
      object_set_id(object, object_id);
      game_add_object(game, object);
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;

}
