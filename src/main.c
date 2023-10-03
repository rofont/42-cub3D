#include "cube.h"

int main(int ac, char **av)
{
    t_map *map;

    map = f_init_map();
    f_pars_file(ac, av, map);
    f_print_map(map);
    return (EXIT_SUCCESS);
}
