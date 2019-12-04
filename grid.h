/**
 * grid.h - Store/retrieve things in (x, y) coordinates
 *
 * Yes, you can always use a 2d array. But grids are sparse, only using memory
 * for locations that actually have things in them.
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#ifndef grid_h
#define grid_h

typedef struct grid grid_t;

/**
 * Create a grid of the given max dimensions. It will have an initial refcount
 * of 1.
 */
grid_t *grid_alloc(int width, int height);

/**
 * Ref/deref a grid, destroying it if
 */
void grid_ref(grid_t *grid);
void grid_deref(grid_t *grid);

/**
 * Put `userdata` (a pointer to anything) at (x, y).
 */
void grid_put(grid_t *grid, void *obj, int x, int y);

/**
 * Get whatever is at (x, y). Returns NULL if nothing is there.
 */
void *grid_get(grid_t *grid, int x, int y);

/**
 * Remove whatever is at (x, y) and return it. Returns NULL if nothing is
 * there.
 */
void *grid_remove(grid_t *grid, int x, int y);

#endif
