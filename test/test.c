#include <assert.h>
#include <gcu.h>


int main(int argc, char **argv)
{
        void *mem = mem_alloc(10, 0);
        mem_deref(mem);

        char *str = str_printf("Hello %s", "world");

        /* hash tests */
        hash_t *hash = hash_alloc(10);
        assert(hash_empty(hash));
        assert(!hash_has(hash, 23));

        hash_insert(hash, 23, str);
        assert(!hash_empty(hash));
        assert(hash_has(hash, 23));

        hash_clear(hash);
        assert(hash_empty(hash));
        assert(!hash_has(hash, 23));

        mem_deref(hash);

        /* grid tests */
        grid_t *grid = grid_alloc(1, 1);

        grid_put(grid, 0, 0, str);
        void *ptr = grid_get(grid, 0, 0);
        assert(ptr == str);

        grid_remove(grid, 0, 0);
        assert(grid_get(grid, 0, 0) == NULL);

        mem_deref(grid);

        octree_t *root = octree_alloc();
        octree_set_depth(root, 3);
        v3_t c1 = {1, 1, 2};
        assert(octree_insert(root, c1, str));
        octree_printf(root, 0);
        assert(octree_lookup(root, c1, &ptr));
        assert(ptr==str);

        v3_t c2 = {-1, -1, -2};
        octree_insert(root, c2, str);
        octree_printf(root, 0);
        assert(octree_lookup(root, c2, &ptr));
        assert(ptr==str);
        

        
        mem_deref(root);

        mem_deref(str);
        
        return 0;
}
