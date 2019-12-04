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

typedef struct hash hash_t;

/**
 * Create a new hash table. `size` is proportional to how much space it will
 * use when empty. Lookups and insertions will be proportional to n_keys/size
 * if your keys are evenly distributed.
 */
hash_t *hash_alloc(int size);
void hash_deref(hash_t * hash);

/**
 * Return non-zero iff the key exists.
 */
int hash_has(hash_t * hash, int key);

/**
 * Lookup the key. If not found returns 0, else returns non-zero and `*obj`
 * will be the pointer to the userdata.
 */
int hash_lookup(hash_t * hash, int key, void **obj);

/**
 * Remove a key and deref its userdata, returning nonzero iff the key exists.
 */
int hash_remove(hash_t * hash, int key);

/**
 * Remove all keys and deref all userdata.
 */
void hash_clear(hash_t * hash);

/**
 * Insert an object at the key, overwriting and derefing any existing object.
 */
void hash_insert(hash_t * hash, int key, void *obj);

#endif
