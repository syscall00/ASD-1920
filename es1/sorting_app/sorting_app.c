#include "../include/sorting.h"
#include "../include/my_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   	

#define MAX_ARRAY_SIZE  20000000
#define MAX_STRING_SIZE 20
#define MAX_BUFFER_SIZE 10

#define RED     "\033[31m"     
#define RESET   "\033[0m"

// path of csv input file
#define INPUT_FILE    "../data/records.csv"

// output log file path
#define LOG_FILE      "../data/log.txt"

// Defines the type of records read from file
typedef struct {
  int f1;
  char *f2;
  int f3;
  double f4;
} record;

// User defined options
typedef struct {
  cmpFnc comparison_fun;  // comparison function to be used 
  char sort_algorithm;    // sorting alghoritm to be used                                
  long n_record; // max number of line to be read
} Options;


int compare_string (record* obj1, record* obj2) {
  return strcmp(obj1->f2, obj2->f2);
}

int compare_int (record* obj1, record* obj2) {
  return obj1->f3-obj2->f3;
}

int compare_float (record* obj1, record* obj2) {
  if (obj1->f4>obj2->f4 )
    return 1;
  else if (obj1->f4 == obj2->f4)
    return 0;
  else return -1;
}

Options parse_options() { 
  Options options;
  int val;
  char* buffer = malloc(sizeof(char)*MAX_BUFFER_SIZE);

  cmpFnc comp_funcs[] = {(cmpFnc) compare_int, (cmpFnc) compare_float, (cmpFnc) compare_string};
    
  printf("Select which field do you want to sort[1]:\n1)Int\n2)Float\n3)String\n");
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
    
  val = buffer[0] == '\n'? 1 : atoi(buffer);

  if(val < 1 || val > 3) {
    printf("Invalid selection for sorting function. Insert a value in [1...3]\n");
    exit(EXIT_FAILURE);
  }
  options.comparison_fun = comp_funcs[val-1];

  printf("Insert number of records to be sorted[%d]: ", MAX_ARRAY_SIZE);
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  options.n_record = buffer[0] == '\n'? MAX_ARRAY_SIZE : atoi(buffer);

  if(options.n_record <= 0 || options.n_record > MAX_ARRAY_SIZE) {
    printf("Invalid max number records. Insert a value in [1...%d]\n", MAX_ARRAY_SIZE);
    exit(EXIT_FAILURE);
  }

  printf("Insert sorting function[1]:\n1)quicksort\n2)insertion sort\n");
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  val = buffer[0] == '\n'? 1 : atoi(buffer);

  if(val != 1 && val != 2) {
    printf("Invalid sorting algorithm. Insert a value in [1...2]\n");
    exit(EXIT_FAILURE);
  }

  options.sort_algorithm = val == 1? 'q' : 'i';

  free(buffer);
  return options;
}

void log_record(myArray *array, int n) {
  FILE *file = fopen(LOG_FILE,"w");
  if (!file) {
    printf("No such file or directory %s\nCan't save log file.\n",LOG_FILE);
    exit(EXIT_FAILURE);
  }

  int size = myArray_size(array);
  for(int i = 0; i < size; i++ ) {
       
    record *rec = myArray_get(array,i);
    fprintf(file, "%d, %s, %d, %f \n",rec->f1,rec->f2,rec->f3,rec->f4);
  }
  fclose(file);
  printf("Saved %d records.\n",n);
}

myArray *array_load(char *path, int max_record_read) {

  FILE *file;
  int count = 0;
  myArray *array;
  file = fopen(path, "r");
  if (!file) {
    printf("No such file or directory %s\n",path);
    exit(EXIT_FAILURE);
  }
  array = myArray_new(max_record_read);

  while (!feof(file) && count < max_record_read ) {
    record *row = malloc(sizeof(record));    
    row->f2 = malloc(sizeof(char)*MAX_STRING_SIZE);  

    int n = fscanf(file, "%d,%1024[^,],%d,%lf", &row->f1,row->f2,&row->f3,&row->f4);

    if(n != 4) {
      if(feof(file)) continue;

      printf("Error while reading file at line: %d.\nMake sure your file is formatted properly.\n", count);
      exit(EXIT_FAILURE);
    }
    myArray_insert(array, row);

    count++;
  }
  fclose(file);
  return array;
}

int main(int argc, char *argv[]) { 
  clock_t start_complexive_timer, end_complexive_time, end_time_load, start_time_sort, end_time_sort;
  double time_taken;
  Options opt = parse_options();
  printf("Loading records in ram...\n");
    
  start_complexive_timer = clock();
	
  myArray *s = array_load(INPUT_FILE,opt.n_record);

  end_time_load = clock(); 
  time_taken = (double)(end_time_load - start_complexive_timer)/CLOCKS_PER_SEC; 
  printf(RED "[OK]Data loaded succesfully in %f seconds.\n" RESET,time_taken);

  if(opt.sort_algorithm == 'i') {
    start_time_sort = clock();
    printf("Start sorting %d records with Insertion sort\n", opt.n_record);

    insertion_sort(s, opt.comparison_fun); 
    
    end_time_sort = clock();
    time_taken = (double)(end_time_sort - start_time_sort)/CLOCKS_PER_SEC;
    printf(RED "[OK]Sorting completed in %f seconds\n" RESET, time_taken); 

  }
  else if(opt.sort_algorithm == 'q') { 
    start_time_sort = clock();
    printf("Start sorting %d records with Quick sort \n", opt.n_record);
    
    quick_sort(s, opt.comparison_fun);

    end_time_sort = clock();
    time_taken = (double)(end_time_sort - start_time_sort)/CLOCKS_PER_SEC; 
    printf(RED "[OK]Sorting completed in %f seconds\n" RESET, time_taken); 

  }

  printf("Saving log file...\n");
  log_record(s,opt.n_record);

  myArray_free(s);

  end_complexive_time = clock();
  time_taken = (double)(end_complexive_time - start_complexive_timer)/CLOCKS_PER_SEC; 
  printf(RED "[OK]Done. Complexive time program: %f seconds\n" RESET, time_taken); 

  return 0; 
} 