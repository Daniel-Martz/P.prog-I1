/** 
 * @brief It declares the tests for the set module
 * 
 * @file space_test.h
 * @author Jaime Romero
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

#include "test.h"
#include "set.h"

void test1_set_create ();
void test2_set_create ();

void test1_set_add ();
void test2_set_add ();
void test3_set_add ();

void test1_set_del ();
void test2_set_del ();
void test3_set_del ();

long test1_set_get_nids();
long test2_set_get_nids();

void test1_set_id_is_there();
void test2_set_id_is_there();
void test3_set_id_is_there();

void test1_set_get_ids();
void test2_set_get_ids();

#endif
