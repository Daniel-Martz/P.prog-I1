/**
 * @brief It defines the Set module (Set structure and its functions)
 * 
 * @file set.h
 * @author Jaime Romero
 * 
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 */
#ifndef SET_H
#define SET_H

#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SET 100

typedef struct _Set Set;

/**
 * @brief Creates the strcuture 'Set', allocating memory and initializing its arguments
 * 
 * @author Jaime Romero
 * 
 * @return A pointer to set with the structure (and its arguments) created
 */
Set* set_create ();

/**
 * @brief "Destroys" the set of elements and frees its memory
 * 
 * @author Jaime Romero
 * 
 * @param set A pointer to the structure
 * 
 * @return OK if everything worked correctly, ERROR if it didn't
 */
Status set_destroy (Set* set);

/**
 * @brief Prints the array of elements (ids) 
 * 
 * @author Jaime Romero
 * 
 * @param set A pointer to Set structure
 * 
 * @return OK if everything worked correctly, ERROR if it didn't
 */
Status set_print (Set* set);


/**
 * @brief Adds a new element to the array of elements in set
 * @author Jaime Romero
 * 
 * @param set A pointer to Set structure
 * @param Id The new id which is going to be added
 * 
 * @return OK if everything worked correctly, ERROR if it didn't
 */
Status add_set (Set* set, Id id);

/**
 * @brief Deletes an element from the array of ids in set
 * 
 * @author Jaime Romero
 * 
 * @param set A pointer to Set structure
 * @param Id The Id which is going to be deleted
 * 
 * @return OK if everything worked correctly, ERROR if it didn't
 */
Status del_set (Set* set, Id id);

#endif