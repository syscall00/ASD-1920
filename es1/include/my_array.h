#pragma once

typedef struct _myArray myArray;
typedef int (*cmpFnc)(void*, void*) ;

/**
 * Create new myArray object
 * @param capacity	initial capacity of the array
 * @return Pointer to new myArray object
 */
myArray* myArray_new(int capacity);

/**
 * Frees up the space of a specific myArray object
 * @param arr	object to be freed
 */
void myArray_free(myArray* arr);

/**
 * Insert new element into a myArray object
 * @param arr	myArray in which save element
 * @param obj	object to be added
 */
void myArray_insert(myArray* arr, void* obj);

/**
 * Insert new element into a myArray object
 * @param arr	myArray in which remove element
 * @param i	index of the object to be removed
 */
void myArray_remove(myArray* arr, int i);

/**
 * Insert new element into a myArray object
 * @param arr	myArray object
 * @param i	myArray in which get element
 * @return Pointer to the object requested
 */
void* myArray_get(myArray* arr, int i);

/**
 * Get the size of a myArray object
 * @param arr	myArray object
 * @return Cardinality of myArray object 
 */
int myArray_size(myArray* arr);

/**
 * Set a specific element by index in myArray object
 * @param arr	    myArray object
 * @param i	      index of element to be set
 * @param element	value of object to be set
 */
void myArray_set(myArray* arr , int i, void* element);

/**
 * Swap two elements in myArray object
 * @param arr	myArray object
 * @param i	  index of first element
 * @param j 	index of second element
 */
void myArray_swap(myArray* arr, int i, int j);