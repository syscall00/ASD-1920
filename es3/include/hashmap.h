#pragma once

typedef int (*hashFnc)(void*);
typedef int (*cmpFnc)(void*,void*);

typedef struct _node node;
typedef struct _table hashMap;

/**
 * Create new hashMap object
 * @param capacity	initial capacity of the hashMap
 * @param hash	hash function 
 * @return      Pointer to new hashMap object
 */
hashMap* hashMap_create(int capacity, hashFnc hash, cmpFnc compare);

/**
 * Frees up the space of a specific hashMap object
 * @param ht	object to be freed
 */
void hashMap_free(hashMap* ht);


/**
 * Check if hashMap object is empty
 * @param ht	hashMap object
 * @return    returns 1 if hashmap is empty, 0 if not
 */
int hashMap_empty(hashMap *ht);


/**
 * Get the number of associations in hashMap
 * @param ht	hashMap object
 * @return    number of associations in hashMap
 */
int hashMap_size(hashMap *ht);


/**
 * Delete all associations in hashMap
 * @param ht	hashMap object
 */
void hashMap_flush(hashMap* ht);


/**
 * Check if exists a specific key in hashmap
 * @param ht	hashMap object
 * @param key	key to be checked
 * @return    returns 1 if key exists, 0 if not
 */
int hashMap_existing_key(hashMap *ht, void *key);


/**
 * Insert a new association <K,V> (key, value)
 * @param ht	hashMap object
 * @param key	key to be inserted
 * @param val	value to be associated
 */
void hashMap_insert(hashMap *ht, void* key, void* val);


/**
 * Return the value associated to the specified key
 * @param ht	hashMap object
 * @param key	key of the element wanted
 * @return    value associated to specified key
 */
void* hashMap_get_val(hashMap *ht, void *key);


/**
 * Delete specific key from hashMap
 * @param ht	hashMap object
 * @param ht	key of the element to be deleted
 */
void hashMap_delete_key(hashMap* ht, void* key);


/**
 * Get the max capacity of hasMap
 * @param ht	hashMap object
 * @return    max number of elements in hashMap
 */
int hashMap_capacity(hashMap *ht);


/**
 * Get all keys in hashmap
 * @param ht	hashMap object
 * @return    array with all keys in hashMap
 */
void** hashMap_get_keys(hashMap* ht);
