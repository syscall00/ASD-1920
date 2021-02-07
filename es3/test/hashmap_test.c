#include "../include/hashmap.h"
#include "../Resources/C/Unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE    10

static int* int_new(int n) {
  int* result = (int*) malloc(sizeof(int));
  *result = n;
  return result;
}

static int compare_strings(char* obj1, char* obj2) {
  return strcmp(obj1,obj2);
}

static int hash(char* key){
  unsigned int ret = 0;
  for(; *key != '\0'; key++) 
    ret+=*key;  
  return ret%MAP_SIZE;
}

static void hashMap_empty_test() {
  hashMap* ht = hashMap_create(0,(hashFnc)hash, (cmpFnc) compare_strings);
  
  TEST_ASSERT_EQUAL(1, hashMap_empty(ht));
  TEST_ASSERT_EQUAL(0, hashMap_size(ht)); 
  TEST_ASSERT_EQUAL(0, hashMap_capacity(ht)); 

  hashMap_free(ht);
}

static void hashMap_insert_test() {
  hashMap* ht = hashMap_create(MAP_SIZE,(hashFnc)hash, (cmpFnc) compare_strings);
  
  char* keys[] = {"key1", "key2", "key3"};
  int* values[] = {int_new(63),int_new(134),int_new(12)};

  hashMap_insert(ht, keys[0], values[0]);
  hashMap_insert(ht, keys[1], values[1]);
  hashMap_insert(ht, keys[2], values[2]);

  hashMap_free(ht);
}



static void hashMap_findAndGet_test() {
  hashMap* ht = hashMap_create(MAP_SIZE,(hashFnc)hash, (cmpFnc) compare_strings);
  char* keys[] = {"key1", "key2", "key3"};
  int* values[] = {int_new(63),int_new(134),int_new(12)};

  hashMap_insert(ht, keys[0], values[0]);
  hashMap_insert(ht, keys[1], values[1]);
  hashMap_insert(ht, keys[2], values[2]);

  TEST_ASSERT_EQUAL(1, hashMap_existing_key(ht, keys[0]));
  TEST_ASSERT_EQUAL(0, hashMap_existing_key(ht, "NotExistingKey"));

  TEST_ASSERT_EQUAL(63, *(int*)hashMap_get_val(ht, keys[0]));

  hashMap_free(ht);
}


static void hashMap_deleteKey_test() {
  hashMap* ht = hashMap_create(MAP_SIZE,(hashFnc)hash, (cmpFnc) compare_strings);
  char* keys[] = {"key1", "key2", "key3"};
  int* values[] = {int_new(63),int_new(134),int_new(12)};

  hashMap_insert(ht, keys[0], values[0]);
  hashMap_insert(ht, keys[1], values[1]);
  hashMap_insert(ht, keys[2], values[2]);
  hashMap_delete_key(ht, keys[1]);

  TEST_ASSERT_EQUAL(0, hashMap_existing_key(ht, keys[1]));
  TEST_ASSERT_EQUAL(2, hashMap_size(ht));

  hashMap_free(ht);
}


static void hashMap_flush_test() {
  hashMap* ht = hashMap_create(MAP_SIZE,(hashFnc)hash, (cmpFnc) compare_strings);
  
  char* keys[] = {"key1", "key2", "key3"};
  int* values[] = {int_new(63),int_new(134),int_new(12)};

  hashMap_insert(ht, keys[0], values[0]);
  hashMap_insert(ht, keys[1], values[1]);
  hashMap_insert(ht, keys[2], values[2]);
  hashMap_flush(ht);

  TEST_ASSERT_EQUAL(0, hashMap_existing_key(ht, keys[0]));
  TEST_ASSERT_EQUAL(0, hashMap_existing_key(ht, keys[1]));
  TEST_ASSERT_EQUAL(0, hashMap_existing_key(ht, keys[2]));
  TEST_ASSERT_EQUAL(0, hashMap_size(ht));

  hashMap_free(ht);
}

static void hashMap_getKeys_test() {
  hashMap* ht = hashMap_create(MAP_SIZE,(hashFnc)hash, (cmpFnc) compare_strings);
  
  char* keys[] = {"key1", "key2", "key3"};
  int* values[] = {int_new(63),int_new(134),int_new(12)};

  hashMap_insert(ht, keys[0], values[0]);
  hashMap_insert(ht, keys[1], values[1]);
  hashMap_insert(ht, keys[2], values[2]);
  
  char** getKeys = (char**) hashMap_get_keys(ht);

  TEST_ASSERT_EQUAL(0, strcmp(getKeys[0], keys[2]));
  TEST_ASSERT_EQUAL(0, strcmp(getKeys[1], keys[0]));
  TEST_ASSERT_EQUAL(0, strcmp(getKeys[2], keys[1]));

  hashMap_free(ht);
}

int main(int argc, char *argv[]) { 

  UNITY_BEGIN();

  RUN_TEST(hashMap_empty_test);
  RUN_TEST(hashMap_insert_test);
  RUN_TEST(hashMap_findAndGet_test);
  RUN_TEST(hashMap_deleteKey_test);
  RUN_TEST(hashMap_flush_test);
  RUN_TEST(hashMap_getKeys_test);

  UNITY_END();

}


