#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

struct _Player {
    Id id;
    char name[WORD_SIZE];
    Id location; 
    Id object;
};

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
    newPlayer->object = NO_ID;

    return newPlayer;
}

Status player_destroy (Player* player){

    if (!player) return ERROR;

    free(player);
    player=NULL;
    return OK;
}

Id player_get_id (Player* player){

    if (!player) return NO_ID;
    return player->id;
}

Id player_get_object (Player* player){
    if (!player) return NO_ID;
    return player->object;
}

const char* player_get_name (Player* player){
    if (!player) return NULL;
    return player->name;
}

Id player_get_location (Player* player){
    if (!player) return NO_ID;
    return player->location;
}

Status player_set_id (Player* player, Id id){
    if (!player) return ERROR;
    player->id = id;
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

Status player_set_object (Player* player, Id object){
    if (!player) return ERROR;
    player->object = object;
    return OK;
}

Status player_set_location (Player* player, Id location){
    if (!player) return ERROR;
    player->location = location;
    return OK;
}

Status player_print (Player* player){
    if (!player) return ERROR;

    fprintf(stdout, " Player ID: %ld\n Name: %s\n Location: %ld\n Object: %ld\n", player->id, player->name, player->location, player->object);
    return OK;
}
