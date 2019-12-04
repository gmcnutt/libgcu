/**
 * grid.h - Store/retrieve things in (x, y) coordinates
 *
 * Yes, you can always use a 2d array. But grids are sparse, only using memory
 * for locations that actually have things in them.
 *
 * Any `userdata` put into a grid will have mem_ref() and mem_deref() called on
 * it, so it should come from mem_alloc().
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#ifndef grid_h
#define grid_h

typedef struct grid grid_t;

/**
 * Create a grid of the given max dimensions. Use mem_deref() to destroy.
 */
grid_t *grid_alloc(int width, int height);

/**
 * Get whatever is at (x, y). Returns NULL if nothing is there.
 */
void *grid_get(grid_t * grid, int x, int y);

/**
 * Put `userdata` (a pointer to anything) at (x, y) and ref it.
 */
void grid_put(grid_t * grid, int x, int y, void *obj);

/**
 * Remove whatever is at (x, y) and deref it.
 */
void grid_remove(grid_t * grid, int x, int y);

#endif
