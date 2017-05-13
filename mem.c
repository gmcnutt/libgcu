/*
 * mem.c - implement the memory allocator
 * Copyright (C) 2016 Gordon McNutt
 */

#include <stdlib.h>

typedef struct {
        unsigned int refcount;
        void (*finalize) (void *ptr);
} mem_t;

static void (*mem_err_handler) (int size) = NULL;

static mem_t *mem_alloc_internal(int size, void (*finalize) (void *))
{
        mem_t *chunk = (mem_t *) calloc(1, sizeof (*chunk) + size);
        if (!chunk) {
                if (mem_err_handler) {
                        mem_err_handler(size);
                }
                return NULL;
        }
        chunk->finalize = finalize;
        return chunk;
}

void *mem_alloc(int size, void (*finalize) (void *))
{
        mem_t *chunk = mem_alloc_internal(size, finalize);
        chunk->refcount = 1;
        return (char *) chunk + sizeof (*chunk);
}

void mem_ref(void *ptr)
{
        mem_t *chunk = (mem_t *) ptr - 1;
        chunk->refcount++;
}

void mem_deref(void *ptr)
{
        mem_t *chunk = (mem_t *) ptr - 1;
        chunk->refcount--;
        if (!chunk->refcount) {
                if (chunk->finalize) {
                        chunk->finalize(ptr);
                }
                free(chunk);
        }
}

void mem_set_err_handler(void (*handler) (int size))
{
        mem_err_handler = handler;
}

unsigned int mem_get_refs(void *ptr)
{
        mem_t *chunk = (mem_t *) ptr - 1;
        return chunk->refcount;
}
