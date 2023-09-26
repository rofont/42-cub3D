#include "cube.h"

int main(int ac, char *av[])
{

    char **ex;
    t_dm *map;
    t_player *play;

    play = NULL;
    play = f_init_player(play);
    f_check_arg(ac, av);
    ex = f_extract_data(av[1]);
    f_print_tab(ex);
    map = f_get_good_map(ex);
    f_print_dm(map);
    if (f_search_player(map, play) != 1)
        f_error(E_FLOODFILL);
    f_print_player(play);
    free(play);
    ft_free_tab_char(ex);
    f_free_dm(map);
    return (EXIT_SUCCESS);
}