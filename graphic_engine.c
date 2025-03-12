/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Daniel Martinez
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define MAX_STR 255 /*Comnstant assigned fpr the maximum length of a string*/
#define WIDTH_MAP 57 /*Constant asignated for the width of the map*/
#define WIDTH_DES 31 /*Constant asignated for the width of the description*/
#define WIDTH_BAN 88 /*Constant asignated for the width of the banner*/
#define HEIGHT_MAP 29 /*Constant asignated for the height of the map*/
#define HEIGHT_BAN 1 /*Constant asignated for the height of the banner*/
#define HEIGHT_HLP 3 /*Constant asignated for the height of help interface*/
#define HEIGHT_FDB 3 /*Constant asignated for the height of feedback interface*/
#define MAX_SIZE 15 /*Constante asignated for the maximum size of the lines inside the space*/
/**
 * @brief This struct stores all the information of the graphic engine (everything showed by screen).
 *
 * @author Daniel Martinez
 */
struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;/*!< It has all the variables needed*/
};

Graphic_engine *graphic_engine_create(void) {
  static Graphic_engine *ge = NULL; /* Assign NULL to *ge only the first time*/

  if (ge) {/* Avoid errors if the function is called multiple times and the graphic engine has already been created. */
    return ge;
  }

  /* Initializates the screen areaa */
  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  /* Initializates the map window area */
  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);

  /* Initializates the descript window area */
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);

  /* Initializates the banner window  area */
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);

  /* Initializates the help window area */
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);

  /* Initializates the feedback window area */
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

Status graphic_engine_print_space(Id space_id, Game *game, Graphic_engine *ge){
  char str[MAX_STR];
  const char* gdesc[N_ROWS];
  Space *space= NULL;
  Id character_id = NO_ID, *objects_id = NULL;
  int names_lenght = 0, i;
  
  if ((space_id == NO_ID) || !game || !ge) return ERROR;

  for (i = 0; i < N_ROWS; i++)
  {
    gdesc[i]=space_get_gdesc(space, i); /*Obtener la descripcion grafica del espacio*/
  }
  space = game_get_space(game, space_id);
  /*COMIENZO*/
  sprintf(str, "  +----------------+");
  character_id = space_get_character(space);
  /*PRIMERA LINEA CON EL CHARACTER*/
  
  if(space_id == game_get_player_location(game)){
    if(character_id != NO_ID){
      sprintf(str, "  | m0^  %s %3d|", character_get_gdesc(game_get_character(game, character_id)), (int)space_id);
    }
    else{
      sprintf(str, "  | m0^         %3d|", (int)space_id);
      }
  }
  else{
    if(character_id != NO_ID){
      sprintf(str, "  |      %s %3d|", character_get_gdesc(game_get_character(game, character_id)), (int)space_id);
    }
    else{
      sprintf(str, "  |             %3d|", (int)space_id);
    }
  }
  screen_area_puts(ge->map, str);
  /*DESCRIPCION DEL MAPA*/
  if(gdesc[0] != NULL){
    for (i = 0; i < N_ROWS; i++) {
      sprintf(str, "  |%s       |", gdesc[i]);
      screen_area_puts(ge->map, str);
    }
  }
  else{
    for (i = 0; i < N_ROWS; i++) {
      screen_area_puts(ge->map, "  |                |");
    }
  }
    /*OBJETOS*/
    objects_id = space_get_objects_ids(space);
    if(objects_id[0] != NO_ID){
      sprintf(str, "|%s",object_get_name(game_get_object(game,objects_id[0])));
    }
    for(i = 1; i<space_get_nobjects(space); i++){
      sprintf(str,"  %s, %s", str, object_get_name(game_get_object(game,objects_id[i])));
    }
    names_lenght = strlen(str);
    if(names_lenght > MAX_SIZE){
      str[12]='.';
      str[13]='.';
      str[14]='.';
      str[15]='\0';
    }
    screen_area_puts(ge->map, str);
    /*CIERRE*/
    sprintf(str, "  +----------------+");
    screen_area_puts(ge->map, str);

    return OK;
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  /* Declare de needed local variables of the function */
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID, *objects_id = NULL, *characters_id = NULL, object_port = NO_ID;
  Space *space_act = NULL;
  char str[MAX_STR];
  int i=0;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Object **objects;
  Character **characters;

  /*INITIALIZES SOME VARIABLES*/
  screen_area_clear(ge->map);
  if ((id_act = (game_get_player_location(game))) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    object_port = player_get_object(game_get_player(game));
  
    graphic_engine_print_space(id_back, game, ge);
    graphic_engine_print_space(id_act, game, ge);
    graphic_engine_print_space(id_left, game, ge);
    graphic_engine_print_space(id_right, game, ge);
    graphic_engine_print_space(id_next, game, ge);

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  /*PASAMOS ARRAY DE OBJETOS A IDS*/
  objects = game_get_objects(game);
  for(i=0; i < game_get_nobjects(game); i++){
    objects_id[i] = object_get_id(objects[i]);
  }
  /*IMPRESION*/
  if (objects_id != NULL) {
    sprintf(str, "  Objects: ");
    screen_area_puts(ge->descript, str);
    for(i=0; i< game_get_nobjects(game); i++){
      sprintf(str, "%s:\t%i",object_get_name(game_get_object(game,objects_id[i])), (int)objects_id[i]);
      screen_area_puts(ge->descript, str);
    }
  }
  else{
    sprintf(str, "  No objects");
    screen_area_puts(ge->descript, str);
  }
  
  screen_area_puts(ge->descript, "\n");

  /*PASAMOS ARRAY DE CHARACTERS A IDS*/
  characters = game_get_characters(game);
  for(i=0; i< game_get_ncharacters(game) ; i++){
    characters_id[i] = character_get_id(characters[i]);
  }
  /*IMPRESION*/
  if (characters_id != NULL) {
    sprintf(str, "  Characters: ");
    screen_area_puts(ge->descript, str);
    for(i=0; i< game_get_ncharacters(game); i++){
      sprintf(str, "%s:\t%i\t(%i)",character_get_name(game_get_character(game,characters_id[i])), (int)characters_id[i],character_get_health(characters[i]));
      screen_area_puts(ge->descript, str);
    }
  }
  else{
    sprintf(str, "  No characters");
    screen_area_puts(ge->descript, str);
  }

  screen_area_puts(ge->descript, "\n");

  sprintf(str,"  Player\t: %i (%i)",(int)id_act,player_get_health(game_get_player(game)));
  screen_area_puts(ge->descript, str);
  if(object_port != NO_ID){
    sprintf(str, "  Player object: %i",(int)object_port);
    screen_area_puts(ge->descript, str);
  }
  else{
    screen_area_puts(ge->descript, "  PLayer has no object");
  }

  screen_area_puts(ge->descript, "\n");

  if(game_get_message(game) != NULL){
    sprintf(str," Message: %s",game_get_message(game));
    screen_area_puts(ge->descript, str);
  }
  

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game   ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, left or l, right or r, take or t, drop or d, attack or t, chat or c, exit or e");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
  }
}
