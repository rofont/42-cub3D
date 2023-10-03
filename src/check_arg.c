#include "cube.h"

void	f_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

int	f_check_cub(char *str)
{
	str = ft_strrchr(str, '.');
	if (ft_strncmp(str, ".cub", 5) == 0)
		return (1);
	return (0);
}

void	f_check_arg(int argc, char **argv)
{
	int	fd;
	char *str;

	if (argc != 2)
		f_error(E_ARGS_NUM);
	else
	{
		fd = open(argv[1], O_RDONLY);
		str	= get_next_line(fd);
		if (fd < 0 || str == NULL || f_check_cub(argv[1]) == 0)
		{
			close (fd);
			f_error(E_FILE_NAME);
		}
		str = f_freenull(str);
	}
}

void	f_pars_file(int ac, char **av, t_map *map)
{
	char **data;
    t_player * play;

    play = f_init_player();
    f_check_arg(ac, av);
    data = f_extract_data(av[1]);
    f_get_data(map, data);
    f_freenull(data);
    if (f_search_player(map, play) != 1)
        f_error(E_FLOODFILL);
    f_size_maps(map);
    data = f_copy_tab(map->map);
    f_flood_fill(data, map, play->x, play->y);
}
