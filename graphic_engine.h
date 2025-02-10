/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

typedef struct _Graphic_engine Graphic_engine; 

/**
 * @brief It creates the graphic engine doing the allocation of space and establish to every graphic object it dimension
 * @author Daniel Martínez
 * 
 * @param 
 * @return It returns a pointer to the graphic engine or NULL if there is a problem during the allocation
*/
Graphic_engine *graphic_engine_create(void);

/**
 * @brief It destroys the every graphic object of the graphic engine passed by argument and free the memories
 * @author Daniel Martínez
 * 
 * @param ge a pointer to a graphic engine
 * @return nothing
*/
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It is responsible for updating and displaying the game's text-based 
 * graphical interface. It draws the map with the player's and objects' 
 * locations, displays information in different screen areas 
 * (description, banner, help, and feedback), and finally prints the result to the terminal
 * @author Daniel Martínez
 * 
 * @param "ge and game" pointers to a graphic engine struct and to a game struct
 * @return Nothing
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
