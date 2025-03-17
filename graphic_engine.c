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
#define WIDTH_MAP 60 /*Constant asignated for the width of the map*/
#define WIDTH_DES 31 /*Constant asignated for the width of the description*/
#define WIDTH_BAN 89 /*Constant asignated for the width of the banner*/
#define HEIGHT_MAP 29 /*Constant asignated for the height of the map*/
#define HEIGHT_BAN 2 /*Constant asignated for the height of the banner*/
#define HEIGHT_HLP 3 /*Constant asignated for the height of help interface*/
#define HEIGHT_FDB 3 /*Constant asignated for the height of feedback interface*/
#define WIDTH_SPACE 17 /*Constante asignated for the maximum size of the lines inside the space*/
#define HEIGHT_SPACE 9 /*Constante asignated for the maximum size of the columns inside the space*/
/**
 * @brief This struct stores all the information of the graphic engine (everything showed by screen).
 *
 * @author Daniel Martinez
 */
struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;/*!< It has all the variables needed*/
};

/*--------------------------------------PRIVATE FUNCTIONS--------------------------------------*/

/**
 * @brief It frees all the allocated memory for paint_game
 * @author Jaime Romero
 * 
 * @param space A double poinyter to the space which is going to be freed
 */
void free_gengine_paint_game(char**space);

/*--------------------------------------PUBLIC FUNCTIONS--------------------------------------*/


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
  if (!ge->map) {
      free(ge);
      return NULL;
  }

  /* Initializates the descript window area */
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);

  /* Initializates the banner window  area */
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 1, WIDTH_BAN + 3, HEIGHT_BAN);

  /* Initializates the help window area */
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);

  /* Initializates the feedback window area */
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void free_gengine_paint_game(char **space) {
  int i = 0;
  if (space != NULL) {
    for (i = 0; i < HEIGHT_SPACE; i++) {
      if (space[i] != NULL) { 
        free(space[i]);
        space[i] = NULL;
      }
    }
    free(space);
    space = NULL;
  }
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

char **graphic_engine_print_space(Id space_id, Game *game){
  char str[MAX_STR];
  char **strspace;
  const char* gdesc[N_ROWS];
  Space *space= NULL;
  Id character_id = NO_ID, *objects_id = NULL;
  int names_lenght = 0, i, j;
  
  if ((space_id == NO_ID) || !game) return NULL;

  space = game_get_space(game, space_id);

  for (i = 0; i < N_ROWS; i++) {
      gdesc[i] = space_get_gdesc(space, i);
      if (!gdesc[i]) gdesc[i] = "               ";  
  }
  /*ALLOC OF THE MATRIX OF THE SPACE*/
  strspace = (char **)malloc(HEIGHT_SPACE * sizeof(char *));
  if (!strspace) return NULL;

  for (i = 0; i < HEIGHT_SPACE; i++) {
      strspace[i] = (char *)malloc((WIDTH_SPACE + 1) * sizeof(char));
      if (!strspace[i]) {
          for (j = 0; j < i; j++) free(strspace[j]);
          free(strspace);
          return NULL;
      }
  }

  /*COMIENZO*/
  sprintf(strspace[0], "+---------------+");
  character_id = space_get_character(space);
  /*PRIMERA LINEA CON EL CHARACTER*/
  
  if(space_id == game_get_player_location(game)){
    if(character_id != NO_ID){
      sprintf(strspace[1], "| m0^ %6.6s %3d|", character_get_gdesc(game_get_character(game, character_id)), (int)space_id);
    }
    else{
      sprintf(strspace[1], "| m0^        %3d|", (int)space_id);
      }
  }
  else{
    if(character_id != NO_ID){
      sprintf(strspace[1], "|     %6.6s %3d|", character_get_gdesc(game_get_character(game, character_id)), (int)space_id);
    }
    else{
      sprintf(strspace[1], "|            %3d|", (int)space_id);
    }
  }
  /*DESCRIPCION DEL MAPA*/
  if(gdesc[0] != NULL){
    for (i = 0; i < N_ROWS; i++) {
      sprintf(strspace[i+2], "|%s      |", gdesc[i]);
    }
  }
  else{
    for (i = 0; i < N_ROWS; i++) {
      sprintf(strspace[i+2],"|                |");
    }
  }
    /*OBJETOS*/
    objects_id = space_get_objects_ids(space);
    if (objects_id[0] != NO_ID) {
        str[0] = '\0'; 
        for (i = 0; i < space_get_nobjects(space); i++) {
            if (i > 0) {
                strncat(str, ", ", MAX_STR - strlen(str) - 1); 
            }
            strncat(str, object_get_name(game_get_object(game, objects_id[i])), MAX_STR - strlen(str) - 1);
        }
        names_lenght = strlen(str);
        if (names_lenght > WIDTH_SPACE - 2) { 
            strncpy(strspace[7], "|", 1);
            strncat(strspace[7], str, WIDTH_SPACE - 5);
            strncat(strspace[7], "...|", 5);
        } else {
            sprintf(strspace[7], "|%15.15s|", str);
        }
    } else {
        sprintf(strspace[7], "|               |");
    }
    /*CIERRE*/
    sprintf(strspace[8], "+---------------+");

    return strspace;
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  /* Declare de needed local variables of the function */
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID, *objects_location = NULL, *characters_location = NULL, object_port = NO_ID;
  Space *space_act = NULL;
  char str[MAX_STR];
  char **space_empty = NULL;
  char **space_left = NULL ,**space_right = NULL, **space_back = NULL, **space_next = NULL, **space_actual = NULL, **space1 = NULL, **space2 = NULL, **space3 = NULL;
  int i=0, j=0;
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
    id_left = space_get_west(space_act);
    id_right = space_get_east(space_act);
    object_port = player_get_object(game_get_player(game));

    if (space_empty == NULL) { 
      if (!(space_empty = (char **)calloc(HEIGHT_MAP, sizeof(char *)))) {
        return;
      }
      for (i = 0; i < HEIGHT_SPACE; i++) {
        if (!(space_empty[i] = (char *)calloc((WIDTH_SPACE + 1), sizeof(char)))) {
          for (j = 0; j < i; j++) {
            free(space_empty[j]);
          }
          free(space_empty);
          return;
        }
      }
      for (i = 0; i < HEIGHT_SPACE; i++) {
        for (j = 0; j < WIDTH_SPACE; j++) {
          space_empty[i][j] = ' ';
        }
      }
    }

    /*PRINT THE SPACE*/
    space_actual = graphic_engine_print_space(id_act, game);

    if(!(space_left = graphic_engine_print_space(id_left, game))){
      space_left = space_empty;
    }
    if(!(space_right = graphic_engine_print_space(id_right, game))){
      space_right = space_empty;
    }
    if(!(space_next = graphic_engine_print_space(id_next, game))){
      space_next = space_empty;
    }
    if(!(space_back = graphic_engine_print_space(id_back, game))){
      space_back = space_empty;
    }

    /*PRINT THE FIRST BLOCK*/

    space1 = space_empty;
    space2 = space_back;
    space3 = space_empty;

    for(i=0; i<HEIGHT_SPACE; i++){
      sprintf(str,"%s %s %s", space1[i],space2[i],space3[i]);
      screen_area_puts(ge->map,str);
    }

    screen_area_puts(ge->map,"                                                                             ");
    
    space1 = space_left;
    space2 = space_actual;
    space3 = space_right;

    for(i=0; i<HEIGHT_SPACE; i++){
      sprintf(str,"%s %s %s", space1[i],space2[i],space3[i]);
      screen_area_puts(ge->map,str);
    }

    screen_area_puts(ge->map,"                                                                    ");
    
    space1 = space_empty;
    space2 = space_next;
    space3 = space_empty;

    for(i=0; i<HEIGHT_SPACE; i++){
      sprintf(str,"%s %s %s", space1[i],space2[i],space3[i]);
      screen_area_puts(ge->map,str);
    }

    screen_area_puts(ge->map,"                                                                          ");


    /* Paint in the description area */
    screen_area_clear(ge->descript);
    /*PASAMOS ARRAY DE OBJETOS A IDS*/
    objects = game_get_objects(game);
    if(!(objects_location =(Id*)calloc(game_get_nobjects(game),sizeof(Id)))){
      return;
    }
      for(i=0; i < game_get_nobjects(game); i++){
        objects_location[i] = game_get_object_location(game, object_get_id(objects[i]));
      }
    
    /*IMPRESION*/
    if (objects_location != NULL) {
      sprintf(str, "  Objects: ");
      screen_area_puts(ge->descript, str);
      for(i=0; i< game_get_nobjects(game); i++){
        sprintf(str, " %s: %i",object_get_name(game_get_object(game,object_get_id(objects[i]))), (int)objects_location[i]);
        screen_area_puts(ge->descript, str);
      }
    }
    else{
      sprintf(str, "  No objects");
      screen_area_puts(ge->descript, str);
    }
    screen_area_puts(ge->descript, "          ");

    /*PASAMOS ARRAY DE CHARACTERS A IDS*/
    characters = game_get_characters(game);

    if(!(characters_location = (Id*)calloc(game_get_ncharacters(game),sizeof(Id)))){
      return;
    }
    
    for(i=0; i< game_get_ncharacters(game) ; i++){
      characters_location[i] = game_get_character_location(game, character_get_id(characters[i]));
    }
    /*IMPRESION*/
    if (game_get_ncharacters(game) != 0) {
      sprintf(str, "  Characters: ");
      screen_area_puts(ge->descript, str);
      for(i=0; i< game_get_ncharacters(game); i++){
        sprintf(str, " %6.6s : %i (%i)",character_get_gdesc(characters[i]), (int)characters_location[i],character_get_health(characters[i]));
        screen_area_puts(ge->descript, str);
      }
    }
    else{
      sprintf(str, "  No characters");
      screen_area_puts(ge->descript, str);
    }

    screen_area_puts(ge->descript, "       ");

    sprintf(str,"  Player: %i (%i)",(int)id_act,player_get_health(game_get_player(game)));
    screen_area_puts(ge->descript, str);
    if(object_port != NO_ID){
      sprintf(str, "  Player object: %i",(int)object_port);
      screen_area_puts(ge->descript, str);
    }
    else{
      screen_area_puts(ge->descript, "  Player has no object");
    }

    screen_area_puts(ge->descript, "        ");

    if(game_get_message(game) != NULL){
      sprintf(str," Message: %s",game_get_message(game));
      screen_area_puts(ge->descript, str);
    }
    

    /* Paint in the banner area */
    screen_area_puts(ge->banner,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    screen_area_puts(ge->banner, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ The anthill game ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

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

    /* PONER FREES DE LOS ESPACIOS */
    if (space_back != space_empty) {
      free_gengine_paint_game(space_back);
      space_back = NULL;
    }
    if (space_next != space_empty) {
      free_gengine_paint_game(space_next);
      space_next = NULL;
    }
    if (space_right != space_empty) {
      free_gengine_paint_game(space_right);
      space_right = NULL;
    }
    if (space_left != space_empty) {
      free_gengine_paint_game(space_left);
      space_left = NULL;
    }
    if (space_actual != space_empty) {
      free_gengine_paint_game(space_actual);
      space_actual = NULL;
    }
    if (space_empty != NULL) {
      free_gengine_paint_game(space_empty);
      space_empty = NULL;
    }

    free(objects_location);
    free(characters_location);
  }
  
}
