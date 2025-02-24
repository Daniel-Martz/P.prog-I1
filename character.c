#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"

struct _Character
{
    Id id;/*!<    */
    char name[WORD_SIZE];/*!<    */
    char gdesc[G_DESC];/*!<    */
    long health;/*!<    */
    Bool friendly;/*!<    */
    char message[MAX_MESSAGE];/*!<    */
};
