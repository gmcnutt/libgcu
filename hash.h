/**
 * hash.h - simple hash table
 *
 * A simple integer-keyed hash table. The user must create their own keys. This
 * will call mem_ref/mem_deref on inserted objects, so they must have been
 * created using mem_alloc.
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#ifndef hash_h
#define hash_h

#include <stddef.h>
#include <stdbool.h>

#define hash_empty(h) (hash_len(h) == 0)

typedef struct hash hash_t;

/**
 * Create a new hash table. `size` is proportional to how much space it will
 * use when empty. Lookups and insertions will be proportional to n_keys/size
 * if your keys are evenly distributed. Use mem_deref() to destroy.
 */
hash_t *hash_alloc(size_t size);

/**
 * Remove all keys and deref all userdata.
 */
void hash_clear(hash_t * hash);

/**
 * Return non-zero iff the key exists.
 */
bool hash_has(hash_t * hash, size_t key);

/**
 * Insert an object at the key, overwriting and derefing any existing object.
 */
void hash_insert(hash_t * hash, size_t key, void *obj);

/**
 * Return number of keys in the hash.
 */
size_t hash_len(hash_t * hash);

/**
 * Return the object stored at the key iff the key exists else NULL.
 */
void *hash_lookup(hash_t * hash, size_t key);

/**
 * Remove a key and deref its userdata iff the key exists.
 */
void hash_remove(hash_t * hash, size_t key);

#endif
