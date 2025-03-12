/** 
 * @brief It tests character module
 * 
 * @file character_test.c
 * @author Jaime Romero
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "character_test.h"

#define MAX_TESTS 30
#define TEST 10

/** 
 * @brief Main function for set unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)test1_character_create();
  if (all || test == 2)test2_character_create();
  if (all || test == 3)test1_character_get_id ();
  if (all || test == 4)test2_character_get_id ();
  if (all || test == 5)test1_character_get_name();
  if (all || test == 6)test2_character_get_name();
  if (all || test == 7)test1_character_get_gdesc();
  if (all || test == 8)test2_character_get_gdesc();
  if (all || test == 9)test1_character_get_message();
  if (all || test == 10)test2_character_get_message();
  if (all || test == 11)test1_character_get_health();
  if (all || test == 12)test2_character_get_health();
  if (all || test == 13)test1_character_get_friendly();
  if (all || test == 14)test2_character_get_friendly();
  if (all || test == 15)test1_character_set_id ();
  if (all || test == 16)test2_character_set_id ();
  if (all || test == 17)test1_character_set_name();
  if (all || test == 18)test2_character_set_name();
  if (all || test == 19)test3_character_set_name();
  if (all || test == 19)test1_character_set_gdesc();
  if (all || test == 20)test2_character_set_gdesc();
  if (all || test == 20)test3_character_set_gdesc();
  if (all || test == 21)test1_character_set_health();
  if (all || test == 22)test2_character_set_health();
  if (all || test == 22)test3_character_set_health();
  if (all || test == 23)test1_character_set_friendly();
  if (all || test == 24)test2_character_set_friendly();
  if (all || test == 25)test1_character_set_message();
  if (all || test == 26)test2_character_set_message();
  if (all || test == 26)test3_character_set_message();
  
  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_character_create(){
    int result;
    Character* c;
    c = character_create(3);
    result = (c!=NULL);
    PRINT_TEST_RESULT(result);
    character_destroy(c);
}
void test2_character_create(){
    Character* c=NULL;
    PRINT_TEST_RESULT((c = character_create(NO_ID)) == NULL);
}

void test1_character_get_id (){
    Character *c;
    c = character_create(4);
    PRINT_TEST_RESULT(character_get_id(c) != NO_ID);
    character_destroy(c);
}
void test2_character_get_id (){
    Character *c=NULL;
    PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}


void test1_character_get_name(){
    Character *c;
    c = character_create(5);
    character_set_name(c, "pepe");
    PRINT_TEST_RESULT(strcmp(character_get_name(c), "pepe") == 0);
    character_destroy(c);
}
void test2_character_get_name(){
    Character *c=NULL;
    PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_get_gdesc(){
    Character *c;
    const char gdesc[5]={"Pepe"};
    c=character_create(7);
    character_set_gdesc(c, gdesc);
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), gdesc)==0);
    character_destroy(c);
}
void test2_character_get_gdesc(){
    Character *c=NULL;
    PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

void test1_character_get_message(){
    Character *c;
    const char message[5]={"Pepe"};
    c=character_create(8);
    character_set_message(c, message);
    PRINT_TEST_RESULT(strcmp(character_get_message(c), message)==0);
    character_destroy(c);
}
void test2_character_get_message(){
    Character *c=NULL;
    PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

void test1_character_get_health(){
    Character *c;
    int health = 5;
    c=character_create(9);
    character_set_health(c, health);
    PRINT_TEST_RESULT(character_get_health(c) == health);
    character_destroy(c);
}
void test2_character_get_health(){
    Character *c=NULL;
    PRINT_TEST_RESULT(character_get_health(c) != POINT_ERROR);
}

void test1_character_get_friendly(){
    Character *c;
    Bool friendly=TRUE;
    c=character_create(10);
    character_set_friendly(c, friendly);
    PRINT_TEST_RESULT(character_get_friendly(c) == friendly);
    character_destroy(c);
}
void test2_character_get_friendly(){
    Character *c=NULL;
    PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
}

void test1_character_set_id (){
    Character *c;
    c=character_create(11);
    PRINT_TEST_RESULT(character_set_id(c, 13) == OK);
    character_destroy(c);
}
void test2_character_set_id (){
    Character *c=NULL;
    PRINT_TEST_RESULT(character_set_id(c, 23) == FALSE);
}

void test1_character_set_name(){
    Character *c; 
    c = character_create(12);
    PRINT_TEST_RESULT(character_set_name(c, "pepe") == OK);
    character_destroy(c);
}
void test2_character_set_name(){
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_name(c, "hola") == ERROR);
}
void test3_character_set_name(){
    Character *c; 
    c = character_create(12);
    PRINT_TEST_RESULT(character_set_name(c, NULL) == ERROR);
    character_destroy(c);
}

void test1_character_set_gdesc(){
    Character *c; 
    c = character_create(13);
    PRINT_TEST_RESULT(character_set_gdesc(c, "pepe") == OK);
    character_destroy(c);
}
void test2_character_set_gdesc(){
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_gdesc(c, "hola") == ERROR);
}
void test3_character_set_gdesc(){
    Character *c; 
    c = character_create(13);
    PRINT_TEST_RESULT(character_set_gdesc(c, NULL) == ERROR);
    character_destroy(c);
}

void test1_character_set_health(){
    Character *c; 
    c = character_create(14);
    PRINT_TEST_RESULT(character_set_health(c, 5) == OK);
    character_destroy(c);
}
void test2_character_set_health(){
    Character *c; 
    c = character_create(14);
    PRINT_TEST_RESULT(character_set_health(c, -5) == ERROR);
    character_destroy(c);
}
void test3_character_set_health(){
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_health(c, 5) == ERROR);
}

void test1_character_set_friendly(){
    Character *c; 
    c = character_create(15);
    PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
    character_destroy(c);
}
void test2_character_set_friendly(){
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}

void test1_character_set_message(){
    Character *c; 
    c = character_create(16);
    PRINT_TEST_RESULT(character_set_message(c, "HOLA") == OK);
    character_destroy(c);
}
void test2_character_set_message(){
    Character *c; 
    c = character_create(16);
    PRINT_TEST_RESULT(character_set_message(c, NULL) == ERROR);
    character_destroy(c);
}
void test3_character_set_message(){
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_message(c, "HOLA") == ERROR);
}
