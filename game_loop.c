/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

/**
 * @brief It initialices the game and the graphic engine controlling the errors (printing the reason of the failure)
 * @author Daniel Martínez
 *
 * @param "game gengine file_name" a pointer to the game, a double pointer to the graphic engine and a string of the name of the file where the information of the game are
 * @return 1 if everything was good and 0 if not 
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
 * @brief It activates the graphic engine and do the action of the last command selected, it will wait until it recives the next command
 * and it won´t stop until the command introduced say it or the game finish, it also check that there is a graphic engine
 * @author Daniel Martínez
 *
 * @param "game and gengine" that are the structure of the game and a pointer to the grafic engine
 * @return nothing
 */
void game_loop_run(Game game, Graphic_engine *gengine);

/**
 * @brief It destroies the game and the graphic engine
 * @author Daniel Martínez
 *
 * @param "game and gengine" that are the structure of the game and a pointer to the grafic engine
 * @return nothing
 */
void game_loop_cleanup(Game game, Graphic_engine *gengine);

/**
 * @brief Checks if the user has provided a game data file and initializes it
 * @author Daniel Martínez
 *
 * @param "argc and argv" first one refers to the number of arguments passed to the program and the other one is an array of strings with the aruments
 * @return 1 if everything was good and 0 if not
 */
int main(int argc, char *argv[]) {
  Game game;
  Graphic_engine *gengine;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if (!game_loop_init(&game, &gengine, argv[1])) {
    game_loop_run(game, gengine);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_create_from_file(game, file_name) == ERROR) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game game, Graphic_engine *gengine) {
  Command *last_cmd;

  if (!gengine) {
    return;
  }

  last_cmd=game_get_last_command(&game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(&game) == FALSE)) {
    graphic_engine_paint_game(gengine, &game);
    command_get_user_input(last_cmd);
    game_actions_update(&game, last_cmd);
  }

}

void game_loop_cleanup(Game game, Graphic_engine *gengine) {
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
