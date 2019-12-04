/**
 * grid.c - Store/retrieve things in (x, y) coordinates
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#include <gcu.h>

typedef struct {
        struct list list;
        void *userdata;
        int x, y;
} node_t;

struct grid {
        struct list *nodelists;
};

grid_t *grid_new();
void grid_deref(grid_t *grid);

/**
 * Put `obj` at (x, y).
 */
void grid_put(grid_t *grid, void *userdata, int x, int y);

/**
 * Get `obj` at (x, y). Returns NULL if nothing is there.
 */
void *grid_get(grid_t *grid, int x, int y);

/**
 * Remove whatever is at (x, y) and return it. Returns NULL if nothing is
 * there.
 */
void *grid_remove(grid_t *grid, int x, int y);
