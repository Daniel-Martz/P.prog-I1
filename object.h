/**
 * @brief It defines the object module
 * 
 * @file object.h
 * @author Jaime Romero
 * 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#include <stdio.h>
#include <stdlib.h>

#define NAME_SIZE 50

typedef struct _Object Object;

/**
 * @brief Creates a new object from a given Id and name
 * 
 * @author Jaime Romero
 * 
 * @param id Object identifier
 * @param name Object name
 * 
 * @return The created object
 */
Object* object_create (Id id);

/**
 * @brief Destroys an object and frees memory
 * 
 * @author Jaime Romero
 * 
 * @param obj A pointer to the object that needs to be destroyed
 * 
 * @return OK if everything goes well, ERROR if there is a failure
 */
Status object_destroy(Object* obj);

/**
 * @brief Gets the Id of an object
 * 
 * @author Jaime Romero
 * 
 * @param obj A pointer to the object
 * 
 * @return The Id of the object
 */
Id object_get_id(Object* obj); 

/**
 * @brief Assigns an Id to an object. I'm not sure if this function 
 * is necessary since it is not in space.h
 * 
 * @author Jaime Romero
 * 
 * @param obj A pointer to the object
 * @param id A variable for the object's Id
 * 
 * @return OK if everything goes well, ERROR if there is a failure
 */
Status object_set_id (Object* obj, Id id);

/**
 * @brief Assigns a name to an object
 * 
 * @author Jaime Romero
 * 
 * @param obj A pointer to the object
 * @param name A string with the object's name
 * 
 * @return OK if everything goes well, ERROR if there is a failure
 */
Status object_set_name (Object* obj, char* name);

/**
 * @brief Gets the name of the object
 * 
 * @author Jaime Romero
 *
 * @param obj A pointer to the object
 * @return A string with the object's name
 */
const char* object_get_name (Object* obj);

/**
 * @brief Prints the object's information  
 * The function displays the Id and name of the object
 * 
 * @author Jaime Romero
 * 
 * @param obj A pointer to the object
 * 
 * @return OK if everything goes well, ERROR if there is a failure
 */
Status object_print (Object* obj);

#endif

