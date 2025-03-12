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
  if (all || test == 19)test1_character_set_gdesc();
  if (all || test == 20)test2_character_set_gdesc();
  if (all || test == 21)test1_character_set_health();
  if (all || test == 22)test2_character_set_health();
  if (all || test == 23)test1_character_set_friendly();
  if (all || test == 24)test2_character_set_friendly();
  if (all || test == 25)test1_character_set_message();
  if (all || test == 26)test2_character_set_message();
  
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
    Character* c;
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
    int i=0;
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
    int i=0;
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

void test1_character_get_health();
void test2_character_get_health();

void test1_character_get_friendly();
void test2_character_get_friendly();

void test1_character_set_id ();
void test2_character_set_id ();

void test1_character_set_name();
void test2_character_set_name();

void test1_character_set_gdesc();
void test2_character_set_gdesc();

void test1_character_set_health();
void test2_character_set_health();

void test1_character_set_friendly();
void test2_character_set_friendly();

void test1_character_set_message();
void test2_character_set_message();
