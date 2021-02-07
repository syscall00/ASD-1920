#include <stdio.h>
#include <stdlib.h>
#include "../include/hashmap.h"


struct _node {
  void* key;
  void* val;
  struct _node* next;
};

struct _table {
  int capacity;
  int size;
  node **list;
  hashFnc hash;
  cmpFnc compare;
};


hashMap* hashMap_create(int capacity, hashFnc hash, cmpFnc compare) {

  hashMap *ht = (hashMap*)malloc(sizeof(hashMap));

  ht->capacity = capacity;
  ht->size = 0;
  ht->list = (node**)malloc(sizeof(node*) * capacity);

  ht->hash = hash;
  ht->compare = compare;
  return ht;
}


void hashMap_free(hashMap* ht) {

  node *curr, *temp;
  
  for(int i = 0; i < hashMap_capacity(ht); i++) {
    curr = ht->list[i];  
    while(ht->list[i]) {
      temp = ht->list[i];
      ht->list[i] = ht->list[i]->next;
      free(temp);
    }
  }
  free(ht->list);
  free(ht);  
}


int hashMap_empty(hashMap *ht) {
  return ht->size == 0;
}


int hashMap_size(hashMap *ht) {
  return ht->size;
}


void hashMap_flush(hashMap* ht) {

  node *temp;
  for(int i = 0; i < hashMap_capacity(ht); i++) {

    while(ht->list[i]) {
      temp = ht->list[i];
      ht->list[i] = ht->list[i]->next;
      free(temp);
    }
    ht->size = 0;
  }
}


void hashMap_insert(hashMap *ht, void* key, void* val) {

  if(hashMap_existing_key(ht, key) > 0) return;
  int pos = ht->hash(key);
  node *list = ht->list[pos];
  node *newNode = (node*)malloc(sizeof(node));

  newNode->key = key;
  newNode->val = val;
  newNode->next = list;
  ht->list[pos] = newNode;

  ht->size++;

}


int hashMap_existing_key(hashMap *ht, void* key) {
  int pos = ht->hash(key);
  node *curr = ht->list[pos];

  while(curr) {
    
    if(ht->compare(curr->key,key) == 0) {
      return 1;
    }
    curr = curr->next;
  }
  return 0;
}


void* hashMap_get_val(hashMap *ht, void *key) {
  if(!hashMap_existing_key(ht, key)) {
   return NULL;
  }
  
  int pos = ht->hash(key);
  node *curr = ht->list[pos];
  while(curr) {
    if(ht->compare(curr->key,key) == 0) {
      return curr->val;
    }
    curr = curr->next;
  }
  return NULL;
}


void hashMap_delete_key(hashMap* ht, void* key) {
  if(hashMap_existing_key(ht, key) < 0) return;
  int pos = ht->hash(key);
  node *list = ht->list[pos],  *prev = NULL;
  while(list) {
    if(ht->compare(list->key, key) == 0) {

      if(prev == NULL) { 
        node* temp = list;
        ht->list[pos] = list->next;
        free(list);
      }
      else {
        prev->next = list->next;
        free(list);
      }
      ht->size--;
      break;
    }
    prev = list;
    list = list->next;
  }

}


int hashMap_capacity(hashMap *ht) {
  return ht->capacity;
}


void** hashMap_get_keys(hashMap* ht) {
  void** keys = malloc(sizeof(void*) * ht->size);
  node* current;
  for(int i = 0,j = 0;i < ht->capacity; i++) {

    current = ht->list[i];  
    while(current) {
      keys[j++] = current->key;
      current = current->next;  
    }
  }
  return keys;
}
