/**
 * @file player.c
 * @author Daniel Martinez
 * @brief It implements the player module
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 64 /* constant for the max number of characters that the player name will have*/
/**
 * @brief This struct stores all the information of a player.
 *
 * @author Daniel Martinez
 */
struct Player_{
    Id id;
    char name[MAX_NAME];
    Space *location;
    Object *object;
};

Player* player_create(Id id)
{
    Player* newPlayer = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  if(!(newPlayer=(Player*)calloc(1,sizeof(Player)))) return NULL;

  /* Initialization of an empty space*/
  newPlayer->id = id;
  newPlayer->name[0] = "\0";
  newPlayer->location = NULL;
  newPlayer->object = NULL;

  return newPlayer;
}

Status player_destroys(Player* player)
{
    if(!player)
        return ERROR;

    free(player);
    player=NULL;
    return OK;
}

Id player_get_id(Player* player)
{
    if(!player) return NO_ID;

    return player->id;
}

Status player_set_id(Player* player, Id id)
{
    if(!player) return ERROR;

    player->id = id;
    return OK;
}

const char* player_get_name(Player* player)
{
    if(!player) return NULL;

    return player->name;
}

Status player_set_name(Player* player, char* name)
{
    if(!player || !name) return ERROR;


    if(!strcpy(player->name, name)) return ERROR;

    return OK;
}

Space* player_get_location(Player* player)
{
    if(!player) return NULL;

    return player->location;
}

Status player_set_location(Player* player, Space* location)
{
    if(!player || !location) return ERROR;

    player->location = location;
    return OK;
}

Object* player_get_object(Player* player)
{
    if(!player) return NULL;

    return player->object;
}

Status player_set_object(Player* player, Object* object)
{
    if(!player || !object) return ERROR;

    player->object = object;
    return OK;
}

Status player_printf(Player* player)
{
    if(!player) return ERROR;

    fprintf(stdout,"--> Player (Id: %ld; Name: %s)\n",player->id,player->name);

    space_print(player->location);

    object_print(player->object);

    return OK;
}