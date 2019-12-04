#include <gcu.h>
#include <grid.h>

int main(int argc, char **argv)
{
        void *mem = mem_alloc(10, 0);
        mem_deref(mem);

        char *str = str_printf("Hello %s", "world");

        grid_t *grid = grid_alloc(1, 1);
        grid_put(grid, 0, 0, str);
        grid_deref(grid);
        
        str_deref(str);

        return 0;
}
