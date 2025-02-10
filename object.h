/**
 * @file object.h
 * @author Daniel Martinez (you@domain.com)
 * @brief 
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
 * @brief Crea un nuevo objeto a partir de un Id y un nombre 
 * dado
 * 
 * @author Jaime y Dani
 * 
 * @param id Identificador del objeto
 * @param name Nombre del objeto 
 * 
 * @return El objeto creado
*/
Object* object_create (Id id);

/**
 * @brief Destruye un nuevo objeto y libera la memoria
 * 
 * @author Jaime y Dani
 * 
 * @param obj Un puntero al objeto que hay que destruri 
 * 
 * @return OK si todo va bien, ERROR si hay algún fallo
*/
Status object_destroy(Object* obj);

/**
 * @brief Obtiene el Id de un objeto
 * 
 * @author Jaime y Dani
 * 
 * @param obj Un puntero al objeto
 * 
 * @return El Id del objeto
 */
Id object_get_id(Object* obj); 

/**
 * @brief Adjudica un id a un objeto. No sé si esta función es 
 * necesaria ya que no está en space.h
 * 
 * @author Dani y Jaime
 * 
 * @param obj Un puntero al objeto
 * @param id Una variable para el id del objeto
 * 
 * @return OK si todo va bien, ERROR si hay algún fallo
 */
Status object_set_id (Object* obj, Id id);

/**
 * @brief Adjudica un nombre a un objeto
 * 
 * @author Dani y Jaime
 * 
 * @param obj Un puntero al objeto
 * @param name Una cadena con el nombre del objeto
 * 
 * @return OK si todo va bien, ERROR si hay algún fallo
 */
Status object_set_name (Object* obj, char* name);

/**
 * @brief Obtiene el nombre del objeto
 * @author Dani y Jaime
 *
 * @param obj Un puntero al objeto
 * @return  Una cadena con el nombre del objeto
 */
const char* object_get_name (Object* obj);

/**
 * @brief Imprime la informacion del objeto
 * La función mustra el Id y el nombre del objeto
 * 
 * @author Dani y Jaime
 * 
 * @param obj a pointer to the space
 * 
 * @return OK si todo va bien, ERROR si hay algún fallo
 */
Status object_print (Object* obj);

#endif

