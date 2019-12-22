/**
 * octree.h - Store/retrieve things in (x, y, z) coordinates
 *
 * Any `userdata` put into a grid will have mem_ref() and mem_deref() called on
 * it, so it should come from mem_alloc().
 *
 * Copyright (c) 2019 Gordon McNutt
 */

#ifndef libgcu_octree_h
#define libgcu_octree_h

#include <stdbool.h>

typedef int v3_t[3];

typedef struct octree {
        v3_t origin;
        size_t depth;
        size_t width;
        v3_t left;
        v3_t right;
        void *userdata;
        struct octree *children[8];
} octree_t;

octree_t *octree_alloc();

void octree_set_depth(octree_t *tree, size_t depth);

/* Insert and ref the userdata at the coords. */
bool octree_insert(octree_t *root, const v3_t coords, void *userdata);

/* Get userdata at the coords. */
bool octree_lookup(octree_t *root, const v3_t coords, void **userdata);

/* Debug. */
void octree_printf(octree_t *tree, int indent);

/**
 * Remove and deref the userdata at the coords, if any.
 */
void octree_remove(octree_t *root, const v3_t coords);

/**
 * Make it bigger.
 */
void octree_resize(octree_t *root, const v3_t dims);

/**
 * For each leaf node found in the given region, invoke the callback.
 */
void octree_visit(octree_t *root, const v3_t origin, const v3_t dims, void (*cb)(const v3_t coords, void *arg), void *arg);


#endif
