/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Daniel Martinez
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Daniel Martinez
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Daniel Martinez
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief It sets whether the space has an object or not
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @param value a boolean, specifying if in the space there is an object (TRUE) or not (FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_object(Space* space, Id object_id);

/**
 * @brief It gets whether the space has an object or not
 * @author Daniel Martinez
 *
 * @param space a pointer to the space
 * @return a boolean, specifying if in the space there is an object (TRUE) or not (FALSE)
 */
Set* space_get_objects(Space* space);

/**
 * @brief This function gets the number of ids that there are in the space
 * 
 * @author Daniel Martínez
 * 
 * @param space A pointer to the space
 * 
 * @return 0 if there was a problem or no objects, and the number of objects in the space if everything was OK.
 */
long space_get_nobjects(Space* space);

/**
 * @brief It prints the space information This fucntion shows the id and name 
 * of the space, the spaces that surrounds it and wheter it has an object or not.
 * @author Daniel Martinez
 * 
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

/**
 * @brief This function check if an object is in the space
 * 
 * @author Daniel Martínez
 * 
 * @param space A pointer to Space structure
 * @param object_id The object id we want to check
 * 
 * @return ERROR if there was a problem or id is not in the space, OK if the object is in the space
 */
Status space_object_is_there(Space* space, Id object_id);

/**
 * @brief This get the array of objects ids in the space
 * 
 * @author Daniel Martínez
 * 
 * @param space A pointer to Set structure
 * 
 * @return NULL if there was a problem, or the array of objects ids if everything was OK.
 */
Id* space_get_objects_ids(Space* space);

#endif
