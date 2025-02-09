/**
 * @file object.c
 * @author Jaime Romero
 * @brief 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 */
#include "object.h"
#include <string.h>

struct _Object {
    Id id;
    char name[NAME_SIZE];
};

Object* object_create (Id id, const char* name){

    Object *obj=NULL;

    if (id == NO_ID || !name) return NULL;

    obj = (Object*)malloc(sizeof(Object));
    if (!obj) return NULL; 

    obj->id = id;
    
    strncpy(obj->name, name, NAME_SIZE - 1);
    obj->name[NAME_SIZE - 1] = '\0';

    return obj;
}

Status object_destroy(Object* obj){

    if (!obj) return ERROR;

    free(obj);
    obj=NULL;
    return OK;
}

Id object_get_id(Object* obj){

    if (!obj) return NO_ID;

    return obj->id;
}

Status object_set_id (Object* obj, Id id){

    if (!obj) return ERROR;

    obj->id=id;
    return OK;
}

Status object_set_name (Object* obj, char* name){

    if (!obj || !name) return ERROR;

    if (!strcpy(obj->name, name))
    {
        return ERROR;
    }

    return OK;
}

const char* object_get_name (Object* obj){

    if (!obj) return NULL;
    return obj->name;
}

Status object_print (Object* obj){

    if (!obj) return ERROR;

    fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", obj->id, obj->name);

    return OK;
}