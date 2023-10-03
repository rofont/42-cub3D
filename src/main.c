#include "cube.h"

int	main(int ac, char **av)
{
	t_map		*map;
	t_player	*play;

	map = f_init_map();
	play = f_init_player();
	f_pars_file(ac, av, map, play);
	f_print_map(map);
	f_free_player(play);
	f_free_tmap(map);
	return (EXIT_SUCCESS);
}
