#include "cube.h"

//transforme le fichier en char **
char	**f_extract_data(char *file)
{
	if (DEBUG == 1)
		printf(CYA"-----extract_data in-----\n"WHT);
	int fd;
	char *temp;
	char*line;
	char **map_file;

	temp = "pouet";
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd)
	while (temp)
	{
		temp = get_next_line(fd);
		line = f_join_and_free(line, temp);
		f_freenull(temp);
	}
	close (fd);
	map_file = ft_split(line, '\n');
	line = f_freenull(line);
	if (DEBUG == 1)
		printf(GRE"-----extract_data out-----\n"WHT);
	return (map_file);
}

//extrait les données corectement et check si elle sont dans le bon ordre
void	f_get_data(t_map *map, char **dat)
{
	int	size;
	int	i;
	int j;
	if (DEBUG == 1)
		printf(CYA"-----get_data in-----\n"WHT);
	size = 0;
	i = -1;
	j = 0;
	while (dat[size])
		size++;
	while (dat[++i])
	{
		if (f_its_here(dat[i], "NO"))
			map->no = f_pars_direction(dat[i], "NO");
		else if (f_its_here(dat[i], "SO"))
			map->so = f_pars_direction(dat[i], "SO");
		else if (f_its_here(dat[i], "WE"))
			map->we = f_pars_direction(dat[i], "WE");
		else if (f_its_here(dat[i], "EA"))
			map->ea = f_pars_direction(dat[i], "EA");
		else if (f_its_here(dat[i], "F"))
			map->floor = f_return_colors(dat[i], "F");
		else if (f_its_here(dat[i], "C"))
			map->ceiling = f_return_colors(dat[i], "C");
		else
			break ;
	}
	if (!f_is_good_data(map))
		f_error(E_FILE_NAME);
	map->map = ft_calloc(sizeof(char *), size - i + 1);
	while (dat[i])
		map->map[j++] = ft_strdup(dat[i++]);
	if (DEBUG == 1)
		printf(GRE"-----get_data out-----\n"WHT);
}

