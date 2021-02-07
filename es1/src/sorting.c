#include "../include/sorting.h"
#include <stdlib.h>
#include <string.h>

/**
 * partition function needed for quicksort algorithm
 * @param array	   myArray object to be sorted
 * @param low	     index of the first value to be sorted
 * @param high	   index of the last value to be sorted
 * @param compare  compare function
 */
void three_way_partition(myArray * array, int low, int high, int *i, int *j, cmpFnc compare);


/**
 * Recursive quick sort function
 * @param array	   myArray object to be sorted
 * @param low	     index of the first value to be sorted
 * @param high	   index of the last value to be sorted
 * @param compare  compare function
 * Recursively quick sort the myArray object
 */
void q_sort(myArray *array, int low, int high, cmpFnc compare);



void insertion_sort(myArray* array ,cmpFnc compare ) {

  void* key;
  register int i,j;
  for(i = 1; i < myArray_size(array); i++) {
    j = i-1;
    key = myArray_get(array,i);
    while(j >= 0 && compare(myArray_get(array,j),key) > 0) {
      myArray_swap(array,j+1,j);
      j--;
    }
    myArray_set(array, j+1, key);
  }
}


void three_way_partition(myArray * array, int low, int high, int *i, int *j, cmpFnc compare) {
  register int l = low, r = low, u = high;
  void * pivot = myArray_get(array, l);
  while (r <= u) {
    if(compare(myArray_get(array, r), pivot) < 0 ) {
      printf("LESS: scambio %d con %d. l: %d r: %d\n", *(int*) myArray_get(array, r), *(int*) pivot, l+1, r+1);
      myArray_swap(array, l, r);
      l++; r++;
    }
    else if(compare(myArray_get(array, r), pivot) > 0) {
      myArray_swap(array, r, u);
      printf("MAJOR: scambio %d con %d. l: %d r: %d\n", *(int*) myArray_get(array, r), *(int*) pivot, l+1, r+1);

      u--;
    }
    else { 
            printf("EQUALS: l: %d r: %d\n", l+1, r+1);

      r++;
    }
  }
  *i = l;
  *j = r;
}


void q_sort(myArray *array, int low, int high, cmpFnc compare) {
  if(low < high) {
    int left, right;
    printf("STAMPA PRIMA PARTITION low: %d high:%d\n", low, high);
    myArray_print(array);
    three_way_partition(array, low, high, &left, &right, compare);
    printf("\nSTAMPA DOPO PARTITION\n");
    myArray_print(array);
    printf("\n\n\n");
    q_sort(array, low, left-1, compare);
    q_sort(array, right, high, compare);
  }
}


void quick_sort(myArray* array, cmpFnc compare) {
  if(myArray_size(array) > 0){
    
    q_sort(array, 0, myArray_size(array)-1, compare);
  }

}

