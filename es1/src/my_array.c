#include <stdlib.h>
#include "../include/my_array.h"

struct _myArray {
  void** array;
  int capacity;
  int size;
};


myArray* myArray_new(int capacity) {

  myArray* result = (myArray*) malloc(sizeof(myArray));
  result->capacity = capacity;
  result->array = (void**) malloc(sizeof(void*) * result->capacity);
  result->size = 0;

  return result;
}


void myArray_free(myArray* arr) {
  free(arr->array);    
  free(arr);
}


void myArray_insert(myArray* arr, void* obj) {
  if(arr->capacity == arr->size) {
    arr->capacity = arr->capacity*2;
    arr->array = (void**) realloc(arr->array, sizeof(void*) *  arr->capacity);

  }

  arr->array[arr->size] = obj;
  arr->size++;
}


void myArray_remove(myArray* arr, int i) {
  if(i >= arr->size) {
    exit(EXIT_FAILURE);
  }
  if(arr->capacity > arr->size * 2){
    arr->capacity = arr->capacity/2;
    arr->array = (void**) realloc(arr->array, sizeof(void*) *  arr->capacity);

  }

  for(int j = i; j<arr->size-1; j++) {
    arr->array[j] = arr->array[j+1];
  }

  arr->size--;
}

void* myArray_get(myArray* arr, int i) {
  if(i >= arr->size ) {
    exit(EXIT_FAILURE);
  }
  return arr->array[i];
}

int myArray_size(myArray* arr) {
  return arr->size;
}

void myArray_set(myArray* array,int i, void* element){
  if(i >= array->size ) {
    exit(EXIT_FAILURE);
  }

  array->array[i] = element;
}

void myArray_swap(myArray* array, int i, int j){
  if(i >= array->size || j>= array->size){
    exit(EXIT_FAILURE);
  }
  void* temp = array->array[i];
  array->array[i] = array->array[j];
  array->array[j] = temp;
}


void myArray_print(myArray *array) {
  printf("[ ");
  for(int i = 0; i < myArray_size(array); i++) {
    printf("%d , ", *(int*) myArray_get(array, i));
  }
  printf("]\n");

}