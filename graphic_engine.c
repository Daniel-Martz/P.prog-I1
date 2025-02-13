/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
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

#define WIDTH_MAP 48 /*Constant asignated for the width of the map*/
#define WIDTH_DES 29 /*Constant asignated for the width of the description*/
#define WIDTH_BAN 23 /*Constant asignated for the width of the banner*/
#define HEIGHT_MAP 13 /*Constant asignated for the height of the map*/
#define HEIGHT_BAN 1 /*Constant asignated for the height of the banner*/
#define HEIGHT_HLP 2 /*Constant asignated for the height of help interface*/
#define HEIGHT_FDB 3 /*Constant asignated for the height of feedback interface*/

/**
 * @brief This struct stores all the information of the graphic engine (everything showed by screen).
 *
 * @author Daniel Martinez
 */
struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
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

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  /* Declare de needed local variables of the function */
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID; 
  Space *space_act = NULL;
  char obj = '*';
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = (game_get_player_location(game))) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    obj_loc = game_get_object_location(game);

    if (id_back != NO_ID) {
      sprintf(str, "  |        %3d|", (int)id_back);
      screen_area_puts(ge->map, str);
      if(obj_loc == id_back){
        sprintf(str, "  |     %c     |", obj);
        screen_area_puts(ge->map, str);
      }
      else{ 
        sprintf(str, "  |           |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    if (id_act != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^    %3d|", (int)id_act);
      screen_area_puts(ge->map, str);
      if(obj_loc == id_act){
        sprintf(str, "  |     %c     |", obj);
        screen_area_puts(ge->map, str);
      }
      else{ 
        sprintf(str, "  |           |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %3d|", (int)id_next);
      screen_area_puts(ge->map, str);
      if(obj_loc == id_next){
        sprintf(str, "  |     %c     |", obj);
        screen_area_puts(ge->map, str);
      }
      else{ 
        sprintf(str, "  |           |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  if (obj_loc != NO_ID) {
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, exit or e, take or t, drop or d");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
