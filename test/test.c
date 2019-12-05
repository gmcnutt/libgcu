#include <assert.h>
#include <gcu.h>


int main(int argc, char **argv)
{
        void *mem = mem_alloc(10, 0);
        mem_deref(mem);

        char *str = str_printf("Hello %s", "world");

        hash_t *hash = hash_alloc(10);
        //assert(hash_empty(hash));
        mem_deref(hash);

        grid_t *grid = grid_alloc(1, 1);
        grid_put(grid, 0, 0, str);
        void *ptr = grid_get(grid, 0, 0);
        assert(ptr==str);
        grid_remove(grid, 0, 0);
        mem_deref(grid);

        mem_deref(str);

        return 0;
}
