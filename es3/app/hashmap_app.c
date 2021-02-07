#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/hashmap.h"

#define INPUT_FILE    "../data/hashes.csv"

#define MAP_SIZE      6321078
#define ARRAY_SIZE    6321078
#define KEYS_SIZE     10000000

#define RED           "\033[31m"     
#define RESET         "\033[0m"

// Defines the type of records read from file
typedef struct {
  int f1;
  int f2;
} record;


static int compare_ints(int* obj1, int* obj2) {
  return *obj1-*obj2;
}

static int hash(int *key) {
  return *key%MAP_SIZE;
}

void swap(record* a, record* b) { 
    record t = *a; 
    *a = *b; 
    *b = t; 
} 

void three_way_partition(record * array, int low, int high, int *i, int *j) {
  register int l = low, r = low, u = high;
  record pivot = array[l];
  while (r <= u) {
    if(array[r].f1 < pivot.f1 ) {
      swap(&array[l], &array[r]);
      l++; r++;
    }
    else if(array[r].f1 > pivot.f1) {
      swap(&array[r], &array[u]);
      u--;
    }
    else { 
      r++;
    }
  }
  *i = l;
  *j = r;
}

void quick_sort(record *array, int low, int high) {
  if(low < high) {
    int left, right;
    three_way_partition(array, low, high, &left, &right);

    quick_sort(array, low, left-1);
    quick_sort(array, right, high);
  }
}

int binary_search(record arr[], int l, int r, int x) { 
  if (r >= l) { 
    int mid = l + (r - l) / 2; 
  
    if (arr[mid].f1 == x) 
      return mid; 
  
    if (arr[mid].f1 > x) 
      return binary_search(arr, l, mid - 1, x); 
  
    return binary_search(arr, mid + 1, r, x); 
  } 
  
  return -1; 
} 

record* array_load(char *path, int max_record_read) {
  FILE *file;
  int count = 0;
  record *array, r; 
  file = fopen(path, "r");
  if (!file) {
    printf("No such file or directory %s\n",path);
    exit(EXIT_FAILURE);
  }

  array = malloc(sizeof(record)*max_record_read);

  while (!feof(file) && count < max_record_read ) {


    int n = fscanf(file, "%d,%d", &array[count].f1, &array[count].f2);
    if(n != 2) {
      if(feof(file)) continue;

      printf("Error while reading file at line: %d.\nMake sure your file is formatted properly.\n", count);
      exit(EXIT_FAILURE);
    }

    
    count++;

  }
  fclose(file);
  return array;
}

void test_array(int* random_keys) {
  clock_t start_load_time, end_load_time, start_get_time, end_get_time;
  double complexive_time, partial_time_taken;
  int count;
  printf("Loading data in static array\n");

  start_load_time = clock();

  record *array_val = array_load(INPUT_FILE, ARRAY_SIZE);
  quick_sort(array_val, 0, ARRAY_SIZE);

  end_load_time = clock(); 
  partial_time_taken = (double)(end_load_time - start_load_time)/CLOCKS_PER_SEC; 
  complexive_time = partial_time_taken;
  printf(RED "[OK]Data loaded succesfully in static array in %f seconds.\n\n" RESET,partial_time_taken);


  
  printf("Sorting array with quicksort alghoritm\n\n");
  
  count = 0;
  printf("Searching for keys\n");
  
  start_get_time = clock();
  for(int i = 0; i < KEYS_SIZE; i++) {
    if(binary_search(array_val, 0, ARRAY_SIZE-1, random_keys[i]) != -1)
      count++; 
  }

  end_get_time = clock();
  partial_time_taken = (double)(end_get_time - start_get_time)/CLOCKS_PER_SEC; 
  complexive_time += partial_time_taken;
  printf(RED "[OK]Retrieved %d elements in %f seconds.\n" RESET,count, partial_time_taken);
  printf(RED "[OK]Complexive static array time in seconds: %f\n\n" RESET,complexive_time);

  free(array_val);
}



hashMap *map_load(char *path, int max_record_read, hashFnc hash, cmpFnc compare) {

  FILE *file;
  int count = 0;
  hashMap *ht;
  file = fopen(path, "r");
  if (!file) {
    printf("No such file or directory %s\n",path);
    exit(EXIT_FAILURE);
  }

  int *key, *value;

  ht = hashMap_create(max_record_read, hash, compare);
  while (!feof(file) && count < max_record_read ) {

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    int n = fscanf(file, "%d,%d", key, value);

    if(n != 2) {
      if(feof(file)) continue;

      printf("Error while reading file at line: %d.\nMake sure your file is formatted properly.\n", count);
      exit(EXIT_FAILURE);
    }
    hashMap_insert(ht, key, value);

  count++;
  }
  fclose(file);
  return ht;
}


void test_hashMap(int* random_keys) {
  clock_t start_load_time, end_load_time, start_get_time, end_get_time;
  int count;
  double complexive_time, partial_time_taken;

  printf("Loading data in hashmap\n");

  start_load_time = clock();

  hashMap * ht = map_load(INPUT_FILE, MAP_SIZE, (hashFnc) hash, (cmpFnc) compare_ints);
  end_load_time = clock(); 
  partial_time_taken = (double)(end_load_time - start_load_time)/CLOCKS_PER_SEC; 
  complexive_time = partial_time_taken;
  printf(RED "[OK]Data loaded succesfully in hashmap in %f seconds.\n\n" RESET,partial_time_taken);

  printf("Searching for keys\n");
  start_get_time = clock();
  count = 0;
  for(int i = 0; i < KEYS_SIZE; i++) {
    if(hashMap_get_val(ht, &(random_keys[i])) != NULL) 
      count++; 
    
  }
  end_get_time = clock();
  partial_time_taken = (double)(end_get_time - start_get_time)/CLOCKS_PER_SEC; 
  complexive_time+=partial_time_taken;
  printf(RED "[OK]Retrieved %d elements in %f seconds.\n" RESET,count, partial_time_taken);
  printf(RED "[OK]Complexive hashmap time in seconds: %f\n\n" RESET,complexive_time);

  hashMap_free(ht);
}

void fill_with_random(int* array, int lower, int upper, int count) { 
  int i; 
  for (i = 0; i < count; i++) { 
      srand ( i );
    int num = (rand() % (upper - lower + 1)) + lower; 
    array[i] = num;    
  } 
} 

int main(int argc, char* argv[]) {

  int *random_keys, choose = 1;

  random_keys = malloc(sizeof(int)*KEYS_SIZE);
  printf("Filling testing array with random keys\n");
  fill_with_random(random_keys, 0, KEYS_SIZE, KEYS_SIZE);

  printf("Choose which data structure do you want to test[1]:\n1)Hashmap\n2)Array\n");
  scanf("%d", &choose);
  if(choose == 2) 
    test_array(random_keys);
  else  
    test_hashMap(random_keys);
  free(random_keys);

}