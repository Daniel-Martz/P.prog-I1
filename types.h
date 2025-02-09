/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /* It is the constant for the maximun size of a word*/
#define NO_ID -1 /* It is a constant that established not having ID to -1*/

typedef long Id; /* It establishes a new type of "variable" of type long that is the Id */

typedef enum { FALSE, TRUE } Bool; /*It establishes a boolean type of data (True or False)*/

typedef enum { ERROR, OK } Status; /* It establishes a status type of data (ERROR or OK) */

typedef enum { N, S, E, W } Direction; /* It establishes the type of data related to the direction*/

#endif
