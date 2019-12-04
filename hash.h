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

hash_t *hash_alloc(int size);
void hash_deref(hash_t *hash);

int hash_has(hash_t *hash, int key);
int hash_lookup(hash_t *hash, int key, void **obj);
int hash_remove(hash_t *hash, int key);
void hash_clear(hash_t *hash);
void hash_insert(hash_t *hash, int key, void *obj);

#endif
