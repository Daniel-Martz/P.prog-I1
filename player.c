/**
 * @brief It implements the player module
 * @file player.h
 * @author Daniel Martinez y Jaime Romero
 * 
 * @version 0.1
 * @date 2025-02-7
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

/**
 * @brief It stores infomation about a player
 * 
 * @author Daniel Martinez
 * 
 */
struct _Player {
    Id id; /*!<The identification for the player*/
    char name[WORD_SIZE]; /*!<Player's name*/
    Id location; /*!<Player's location (stored as an Id)*/
    Id object_id; /*!<Id of the objcet carried by the player*/
    long health; /*!<Player's healthpoints*/
};

/*============================Init============================*/
Player* player_create (Id id){

    Player *newPlayer=NULL;

    /*Error control*/
    if (id == NO_ID) return NULL;

    newPlayer= (Player*)malloc(sizeof(Player));
    if (!newPlayer) return NULL; 

    /*Initialization of a new Player*/
    newPlayer->id = id;
    newPlayer->name[0] = '\0';
    newPlayer->location = NO_ID;
    newPlayer->object_id = NO_ID;
    newPlayer->health = 0;

    return newPlayer;
}

Status player_destroy (Player* player){

    if (!player) return ERROR;

    free(player);
    return OK;
}

/*============================Get============================*/
Id player_get_id (Player* player){

    if (!player) return NO_ID;
    return player->id;
}

Id player_get_object (Player* player){
    if (!player) return NO_ID;
    return player->object_id;
}

const char* player_get_name (Player* player){
    if (!player) return NULL;
    return player->name;
}

int player_get_health(Player* player){
    if(!player) return NO_ID;
    return player->health;
}

Id player_get_location (Player* player){
    if (!player) return NO_ID;
    return player->location;
}

/*============================Set============================*/
Status player_set_id (Player* player, Id id){
    if (!player) return ERROR;
    player->id = id;
    return OK;
}

Status player_set_object (Player* player, Id object){
    if (!player) return ERROR;
    player->object_id = object;
    return OK;
}

Status player_set_name (Player* player, const char* name){
    if (!player || !name) return ERROR;

    if (!strcpy(player->name, name))
    {
        return ERROR;
    }

    return OK;
}

Status player_set_health(Player* player, int health){
    if (!player || health < 0) return ERROR;

    player->health = health;

    return OK;
}

Status player_set_location (Player* player, Id location){
    if (!player) return ERROR;
    player->location = location;
    return OK;
}

/*============================Print============================*/
Status player_print (Player* player){
    if (!player) return ERROR;

    fprintf(stdout, " Player ID: %ld\n Name: %s\n", player->id, player->name);
    return OK;
}
