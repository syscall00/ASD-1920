
#include "my_array.h"

typedef int (*cmpFnc)(void*,void*);

/**
 * Insertion sort function
 * @param array	   myArray object to be sorted
 * @param compare  compare function
 * Sort a myArray object with insertion sort method
 */
void insertion_sort(myArray* , cmpFnc);

/**
 * Quick sort function
 * @param array   myArray object to be sorted
 * @param compare function
 * Sort a myArray object with quicksort method
 */
void quick_sort(myArray* array, cmpFnc compare);

