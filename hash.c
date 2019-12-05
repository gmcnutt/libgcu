/**
 * hash.c - simple hash table
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#include "hash.h"
#include "list.h"
#include "mem.h"

typedef struct {
        struct list list;
        void *userdata;
        size_t key;
} hashnode_t;

struct hash {
        struct list *buckets;
        size_t n_buckets;
        size_t len;
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

static hashnode_t *hashnode_alloc(void *userdata, size_t key)
{
        hashnode_t *node = mem_alloc(sizeof (*node), hashnode_fin);
        node->userdata = userdata;
        mem_ref(userdata);
        node->key = key;
        return node;
}

static hashnode_t *hash_get_node(hash_t * hash, size_t key)
{
        size_t i = key % hash->n_buckets;
        struct list *elem;
        list_for_each(&hash->buckets[i], elem) {
                hashnode_t *node = (hashnode_t *) elem;
                if (node->key == key) {
                        return node;
                }
        }
        return NULL;
}

static inline void hash_remove_node(hashnode_t * node)
{
        list_remove(&node->list);
        mem_deref(node);
}

hash_t *hash_alloc(size_t size)
{
        hash_t *hash = mem_alloc(sizeof (*hash), hash_fin);
        hash->buckets = mem_alloc(sizeof (struct list) * size, NULL);
        hash->n_buckets = size;
        for (size_t i = 0; i < size; i++) {
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
        for (size_t i = 0; i < hash->n_buckets; i++) {
                struct list *head = &hash->buckets[i];
                struct list *next = head->next;
                while (next != head) {
                        hashnode_t *node = (hashnode_t *) next;
                        next = next->next;
                        hash_remove_node(node);
                }
        }
}

void hash_insert(hash_t * hash, size_t key, void *userdata)
{
        size_t i = key % hash->n_buckets;
        hashnode_t *node = hashnode_alloc(userdata, key);
        list_add(&hash->buckets[i], &node->list);
}

void *hash_lookup(hash_t * hash, size_t key)
{
        hashnode_t *node = hash_get_node(hash, key);
        if (node) {
                return node->userdata;
        }
        return NULL;
}

void hash_remove(hash_t * hash, size_t key)
{
        hashnode_t *node = hash_get_node(hash, key);
        if (node) {
                hash_remove_node(node);
        }
}
