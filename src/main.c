#include "cube.h"

int main(int ac, char *av[])
{

    char **ex;
    t_dm *data;
    t_player *play;
    t_map   *map;

    map = NULL;
    play = NULL;
    play = f_init_player(play);
    f_check_arg(ac, av);
    ex = f_extract_data(av[1]);
    f_print_tab(ex);
    data = f_get_good_map(ex);
    f_print_dm(data);
    if (f_search_player(data, play) != 1)
        f_error(E_FLOODFILL);
    f_print_player(play);
    map = f_maps(map, data);
    f_modif_map(map, data);
    f_print_map(map);
    f_flood_fill(map, play->x, play->y);
    // f_print_map(map);
    free(play);
    ft_free_tab_char(ex);
    f_free_dm(data);
    return (EXIT_SUCCESS);
}