/**
 * grid.c - Store/retrieve things in (x, y) coordinates
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#include "grid.h"
#include "hash.h"
#include "list.h"
#include "mem.h"

#define HASH(x, y) ((x) * (y) + 1)      /* Simple, dumb hash function */

static const float SPARSENESS = 10;     /* Assume 10% occupied. */

/**
 * Use a hash table to implement a grid, hashing on the (x, y) coordinates.
 */
typedef struct {
        struct list list;
        void *userdata;
        size_t x, y;
} node_t;

struct grid {
        hash_t *nodetable;
};


static void grid_fin(void *ptr)
{
        grid_t *grid = (grid_t *) ptr;
        mem_deref(grid->nodetable);
}

grid_t *grid_alloc(size_t width, size_t height)
{
        grid_t *grid = mem_alloc(sizeof (*grid), grid_fin);
        grid->nodetable = hash_alloc((width * height) / SPARSENESS + 1);
        return grid;
}

void grid_put(grid_t * grid, size_t x, size_t y, void *userdata)
{
        hash_insert(grid->nodetable, HASH(x, y), userdata);
}

void *grid_get(grid_t * grid, size_t x, size_t y)
{
        return hash_lookup(grid->nodetable, HASH(x, y));
}

void grid_remove(grid_t * grid, size_t x, size_t y)
{
        hash_remove(grid->nodetable, HASH(x, y));
}
