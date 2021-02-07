#include "../include/sorting.h"
#include "../include/my_array.h"
#include "../Resources/C/Unity/unity.h"
#include <stdio.h>
#include <stdlib.h>

static int* int_new(int n) {
  int* result = (int*) malloc(sizeof(int));
  *result = n;
  return result;
}

static int compare_ints(int* obj1, int* obj2) {
  return *obj1 - *obj2;
}

static void delete_test_objects(myArray* array) {
  for(int i=0; i<myArray_size(array); ++i) {
    free(myArray_get(array, i));
  }

  myArray_free(array);
}

void insertion_sort_best_test() {
  myArray* array = myArray_new(5);
  myArray_insert(array, int_new(3));
  myArray_insert(array, int_new(5));
  myArray_insert(array, int_new(7));
  myArray_insert(array, int_new(11));
  myArray_insert(array, int_new(14));
    
  insertion_sort(array,(cmpFnc) compare_ints);
  TEST_ASSERT_EQUAL(3, *(int*) myArray_get(array, 0));
  TEST_ASSERT_EQUAL(5, *(int*) myArray_get(array, 1));
  TEST_ASSERT_EQUAL(7, *(int*) myArray_get(array, 2));
  TEST_ASSERT_EQUAL(11, *(int*) myArray_get(array, 3));
  TEST_ASSERT_EQUAL(14, *(int*) myArray_get(array, 4));

  delete_test_objects(array);
}

void quick_sort_best_test() {
  myArray* array = myArray_new(5);
  myArray_insert(array, int_new(3));
  myArray_insert(array, int_new(5));
  myArray_insert(array, int_new(7));
  myArray_insert(array, int_new(11));
  myArray_insert(array, int_new(14));

  quick_sort(array, (cmpFnc) compare_ints);
  TEST_ASSERT_EQUAL(3, *(int*) myArray_get(array, 0));
  TEST_ASSERT_EQUAL(5, *(int*) myArray_get(array, 1));
  TEST_ASSERT_EQUAL(7, *(int*) myArray_get(array, 2));
  TEST_ASSERT_EQUAL(11, *(int*) myArray_get(array, 3));
  TEST_ASSERT_EQUAL(14, *(int*) myArray_get(array, 4));

  delete_test_objects(array);
}

void insertion_sort_worst_test() {
  myArray* array = myArray_new(5);
  myArray_insert(array, int_new(14));
  myArray_insert(array, int_new(11));
  myArray_insert(array, int_new(7));
  myArray_insert(array, int_new(5));
  myArray_insert(array, int_new(3));

  insertion_sort(array,(cmpFnc) compare_ints);
  TEST_ASSERT_EQUAL(3, *(int*) myArray_get(array, 0));
  TEST_ASSERT_EQUAL(5, *(int*) myArray_get(array, 1));
  TEST_ASSERT_EQUAL(7, *(int*) myArray_get(array, 2));
  TEST_ASSERT_EQUAL(11, *(int*) myArray_get(array, 3));
  TEST_ASSERT_EQUAL(14, *(int*) myArray_get(array, 4));

  delete_test_objects(array);
}

void quick_sort_worst_test() {
  myArray* array = myArray_new(5);
  myArray_insert(array, int_new(14));
  myArray_insert(array, int_new(11));
  myArray_insert(array, int_new(7));
  myArray_insert(array, int_new(11));
  myArray_insert(array, int_new(3));

  quick_sort(array, (cmpFnc) compare_ints);

  TEST_ASSERT_EQUAL(3, *(int*) myArray_get(array, 0));
  TEST_ASSERT_EQUAL(7, *(int*) myArray_get(array, 1));
  TEST_ASSERT_EQUAL(11, *(int*) myArray_get(array, 2));
  TEST_ASSERT_EQUAL(11, *(int*) myArray_get(array, 3));
  TEST_ASSERT_EQUAL(14, *(int*) myArray_get(array, 4));

  delete_test_objects(array);
}

void insertion_sort_medium_test() {
  myArray* array = myArray_new(5);
  myArray_insert(array, int_new(5));
  myArray_insert(array, int_new(3));
  myArray_insert(array, int_new(11));
  myArray_insert(array, int_new(7));
  myArray_insert(array, int_new(14));

  insertion_sort(array,(cmpFnc) compare_ints);
  TEST_ASSERT_EQUAL(3, *(int*) myArray_get(array, 0));
  TEST_ASSERT_EQUAL(5, *(int*) myArray_get(array, 1));
  TEST_ASSERT_EQUAL(7, *(int*) myArray_get(array, 2));
  TEST_ASSERT_EQUAL(11, *(int*) myArray_get(array, 3));
  TEST_ASSERT_EQUAL(14, *(int*) myArray_get(array, 4));

  delete_test_objects(array);
}

void quick_sort_medium_test() {
  myArray* array = myArray_new(5);
  myArray_insert(array, int_new(5));
  myArray_insert(array, int_new(3));
  myArray_insert(array, int_new(11));
  myArray_insert(array, int_new(7));
  myArray_insert(array, int_new(14));

  quick_sort(array, (cmpFnc) compare_ints);
  TEST_ASSERT_EQUAL(3, *(int*) myArray_get(array, 0));
  TEST_ASSERT_EQUAL(5, *(int*) myArray_get(array, 1));
  TEST_ASSERT_EQUAL(7, *(int*) myArray_get(array, 2));
  TEST_ASSERT_EQUAL(11, *(int*) myArray_get(array, 3));
  TEST_ASSERT_EQUAL(14, *(int*) myArray_get(array, 4));

  delete_test_objects(array);
}


int main(int argc, char *argv[]) { 
  UNITY_BEGIN();

  //RUN_TEST(quick_sort_best_test);
  RUN_TEST(quick_sort_worst_test);
  //RUN_TEST(quick_sort_medium_test);

  //RUN_TEST(insertion_sort_best_test);
  //RUN_TEST(insertion_sort_worst_test);
  //RUN_TEST(insertion_sort_medium_test);

  UNITY_END();

}

 
