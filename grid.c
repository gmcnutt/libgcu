/**
 * grid.c - Store/retrieve things in (x, y) coordinates
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#include "grid.h"
#include "hash.h"
#include "list.h"
#include "mem.h"

static const float SPARSENESS = 10;     /* Assume 10% occupied. */

typedef struct {
        struct list list;
        void *userdata;
        int x, y;
} node_t;

struct grid {
        hash_t *nodetable;
};

static void grid_fin(void *ptr)
{
        grid_t *grid = (grid_t *) ptr;

        /* This will deref all the objects. */
        hash_deref(grid->nodetable);
}

grid_t *grid_alloc(int width, int height)
{
        grid_t *grid = mem_alloc(sizeof (*grid), grid_fin);
        grid->nodetable = hash_alloc((width * height) / SPARSENESS + 1);
        return grid;
}

void grid_deref(grid_t * grid)
{
        mem_deref(grid);
}

void grid_put(grid_t * grid, int x, int y, void *userdata)
{
        /* The hash table will ref the object. */
        int key = x * y + 1;
        hash_insert(grid->nodetable, key, userdata);
}

void *grid_get(grid_t * grid, int x, int y);

void grid_remove(grid_t * grid, int x, int y);
