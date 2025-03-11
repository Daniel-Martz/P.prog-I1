/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "set_test.h"

#define MAX_TESTS 30

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
  
  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test1_set_add();
  if (all || test == 4) test2_set_add();
  if (all || test == 5) test1_set_del();
  if (all || test == 6) test2_set_del();
  if (all || test == 7) test1_set_get_nids();
  if (all || test == 8) test2_set_get_nids();
  if (all || test == 9) test1_set_id_is_there();
  if (all || test == 10) test2_set_id_is_there();
  if (all || test == 11) test1_set_get_ids();
  if (all || test == 12) test2_set_get_ids();
  
  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_set_create (){
    int result;
    Set *s;
    s = set_create();
    result=(s!=NULL);
    PRINT_TEST_RESULT(result);
    set_destroy(s);
}

void test2_set_create (){
    int result;
    Set *s=NULL;
    s = set_create();
    result = (s == NULL);
    PRINT_TEST_RESULT(result);
}

void test1_set_add (){
    Set *s;
    s = set_create();
    PRINT_TEST_RESULT(set_add(s, 10) == OK);
    set_destroy(s);
}

void test2_set_add (){
    Set *s=NULL;
    s = set_create();
    PRINT_TEST_RESULT(set_add(s, 10) == ERROR);
}

void test3_set_add (){
    Set *s;
    s = set_create();
    set_add(s, 10);
    PRINT_TEST_RESULT(set_add(s, 10) == ERROR);
    set_destroy(s);
}

void test1_set_del (){
    Set *s;
    s = set_create();
    set_add(s, 10);
    PRINT_TEST_RESULT(set_del(s, 10) == OK);
    set_destroy(s);
}

void test2_set_del (){
    Set *s=NULL;
    s = set_create();
    PRINT_TEST_RESULT(set_del(s, 10) == ERROR);
}

void test3_set_del (){
    Set *s;
    s = set_create();
    PRINT_TEST_RESULT(set_del(s, 10) == ERROR);
    set_destroy(s);
}

long test1_set_get_nids(){
    Set *s;
    s = set_create();
    PRINT_TEST_RESULT(set_get_nids(s) <= MAX_SET && set_get_nids(s) >= 0);
    set_destroy(s);
}

long test2_set_get_nids(){
    Set *s=NULL;
    s = set_create();
    PRINT_TEST_RESULT(set_get_nids(s) == POINT_ERROR);
}

void test1_set_id_is_there(){
    Set *s;
    s = set_create();
    set_add(s, 10);
    PRINT_TEST_RESULT(set_id_is_there(s, 10) == OK);
    set_destroy(s);
}

void test2_set_id_is_there(){
    Set *s;
    s = set_create();
    PRINT_TEST_RESULT(set_id_is_there(s, 10) == ERROR);
    set_destroy(s);
}

void test3_set_id_is_there(){
    Set *s=NULL;
    s = set_create();
    PRINT_TEST_RESULT(set_id_is_there(s, 10) == ERROR);
}

void test1_set_get_ids(){
    Set *s=NULL;
    s = set_create();
    PRINT_TEST_RESULT(set_get_ids(s) == ERROR);
}

void test2_set_get_ids(){
    Set *s=NULL;
    s = set_create();
    PRINT_TEST_RESULT(set_get_ids(s) == OK);
    set_destroy(s);
}