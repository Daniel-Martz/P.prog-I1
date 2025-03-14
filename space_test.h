/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Jaime Romero
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

#include "space.h"
#include "set.h"
#include "test.h"

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();
void test1_space_set_north();
void test2_space_set_north();
void test3_space_set_north();
void test4_space_set_north();
void test1_space_set_south();
void test2_space_set_south();
void test3_space_set_south();
void test4_space_set_south();
void test1_space_set_east();
void test2_space_set_east();
void test3_space_set_east();
void test4_space_set_east();
void test1_space_set_west();
void test2_space_set_west();
void test3_space_set_west();
void test4_space_set_west();
void test1_space_set_new_object();
void test2_space_set_new_object();
void test1_space_set_character();
void test2_space_set_character();
void test1_space_set_gdesc();
void test2_space_set_gdesc();
void test1_space_get_id();
void test2_space_get_id();
void test1_space_get_name();
void test2_space_get_name();
void test1_space_get_north();
void test2_space_get_north();
void test1_space_get_south();
void test2_space_get_south();
void test1_space_get_east();
void test2_space_get_east();
void test1_space_get_west();
void test2_space_get_west();
void test1_space_get_nobjects();
void test2_space_get_nobjects();
void test1_space_get_objects_ids();
void test1_space_get_character();
void test2_space_get_character();
void test1_space_get_gdesc();
void test2_space_get_gdesc();
void test3_space_get_gdesc();
void test4_space_get_gdesc();

#endif
