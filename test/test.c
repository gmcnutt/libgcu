#include <gcu.h>
#include <grid.h>

int main(int argc, char **argv)
{
        void *mem = mem_alloc(10, 0);
        mem_deref(mem);

        char *str = str_printf("Hello %s", "world");
        str_deref(str);

        grid_t *grid = grid_alloc(1, 1);
        grid_deref(grid);
        
        return 0;
}
