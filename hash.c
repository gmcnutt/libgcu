/**
 * hash.c - simple hash table
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#include <stddef.h>

#include "hash.h"
#include "list.h"
#include "mem.h"

typedef struct {
        struct list list;
        void *userdata;
} hashnode_t;

struct hash {
        struct list *buckets;
        int n_buckets;
        int userefs;
};

static void hash_fin(void *ptr)
{
        hash_t *hash = (hash_t *) ptr;
        hash_clear(hash);
        mem_deref(hash->buckets);
}

static void hashnode_fin(void *ptr)
{
        hashnode_t *node = (hashnode_t *) ptr;
        mem_deref(node->userdata);
}

static hashnode_t *hashnode_alloc(void *userdata)
{
        hashnode_t *node = mem_alloc(sizeof (*node), hashnode_fin);
        node->userdata = userdata;
        mem_ref(userdata);
        return node;
}

hash_t *hash_alloc(int size)
{
        hash_t *hash = mem_alloc(sizeof (*hash), hash_fin);
        hash->buckets = mem_alloc(sizeof (struct list) * size, NULL);
        hash->n_buckets = size;
        for (int i = 0; i < size; i++) {
                list_init(&hash->buckets[i]);
        }
        return hash;
}

void hash_deref(hash_t * hash)
{
        mem_deref(hash);
}

void hash_clear(hash_t * hash)
{
        for (int i = 0; i < hash->n_buckets; i++) {
                struct list *head = &hash->buckets[i];
                struct list *next = head->next;
                while (next != head) {
                        hashnode_t *node = (hashnode_t *) next;
                        next = next->next;
                        list_remove(&node->list);
                        mem_deref(node);
                }
        }
}

void hash_insert(hash_t * hash, int key, void *userdata)
{
        int i = key % hash->n_buckets;
        hashnode_t *node = hashnode_alloc(userdata);
        list_add(&hash->buckets[i], &node->list);
}
