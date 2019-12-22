#include <assert.h>
#include <stdio.h>

#include "mem.h"
#include "octree.h"

static void octree_fin(void *ptr)
{
        octree_t *tree = (octree_t*)ptr;
        for (int i = 0; i < 8; i++) {
                octree_t *child = tree->children[i];
                if (child) {
                        mem_deref(child);
                }
        }
        if (tree->userdata) {
                mem_deref(tree->userdata);
        }
}

octree_t *octree_alloc(void)
{
        return mem_alloc(sizeof(octree_t), octree_fin);
}

void octree_set_depth(octree_t *tree, size_t depth)
{
        tree->depth = depth;
        tree->width = (1 << depth);

        tree->left[0] = tree->origin[0] - tree->width / 2;
        tree->left[1] = tree->origin[1] - tree->width / 2;
        tree->left[2] = tree->origin[2] - tree->width / 2;
        
        tree->right[0] = tree->origin[0] + tree->width / 2;
        tree->right[1] = tree->origin[1] + tree->width / 2;
        tree->right[2] = tree->origin[2] + tree->width / 2;
}

void octree_printf(octree_t *tree, int indent)
{
        printf("%*c(%d, %d, %d) [%d, %d, %d] %p\n",
               indent, ' ',
               tree->left[0], tree->left[1], tree->left[2],
               tree->right[0], tree->right[1], tree->right[2],
                tree->userdata);
        for (int i = 0; i < 8; i++) {
                octree_t *child = tree->children[i];
                if (child) {
                        octree_printf(child, indent + 2);
                }
        }
        
}
      
bool octree_contains(octree_t *tree, const v3_t coords)
{
        /* Error case. */
        return (coords[0] >= tree->left[0] &&
                coords[0] < tree->right[0] &&
                coords[1] >= tree->left[1] &&
                coords[1] < tree->right[1] &&
                coords[2] >= tree->left[2] &&
                coords[2] < tree->right[2]);

}

bool octree_insert(octree_t *root, const v3_t coords, void *userdata)
{
        /* Base case. */
        if (root->depth == 0) {
                assert(root->origin[0] == coords[0]);
                assert(root->origin[1] == coords[1]);
                assert(root->origin[2] == coords[2]);
                mem_ref(userdata);
                root->userdata = userdata;
                return true;
        }

        /* Find child quadrant. */
        int x = coords[0] >= root->origin[0] ? 1 : 0;
        int y = coords[1] >= root->origin[1] ? 1 : 0;
        int z = coords[2] >= root->origin[2] ? 1 : 0;
        int index = x * 4 + y * 2 + z;
        
        octree_t *child = root->children[index];
        if (! child) {
                child = octree_alloc();
                child->origin[0] = root->origin[0] + (x > 0 ? 1 : -1) * root->width / 4;
                child->origin[1] = root->origin[1] + (y > 0 ? 1 : -1) * root->width / 4;
                child->origin[2] = root->origin[2] + (z > 0 ? 1 : -1) * root->width / 4;
                octree_set_depth(child, root->depth - 1);
                root->children[index] = child;
        }

        return octree_insert(child, coords, userdata);
}

bool octree_lookup(octree_t *root, const v3_t coords, void **userdata)
{
        /* Base case. */
        if (root->depth == 0) {
                *userdata = root->userdata;
                return true;
        }

        /* Find child quadrant. */
        int x = coords[0] >= root->origin[0] ? 1 : 0;
        int y = coords[1] >= root->origin[1] ? 1 : 0;
        int z = coords[2] >= root->origin[2] ? 1 : 0;
        int index = x * 4 + y * 2 + z;
        
        octree_t *child = root->children[index];
        if (! child) {
                return false;
        }

        return octree_lookup(child, coords, userdata);
}
