#include "cube.h"

void	f_print_dm(t_dm *data_map)
{
	printf("---------data_map in------------\n");
	printf("NO =%s=\n", data_map->no);
	printf("SO =%s=\n", data_map->so);
	printf("WE =%s=\n", data_map->we);
	printf("EA =%s=\n", data_map->ea);
	printf("F =%s=\n", data_map->floor);
	printf("C =%s=\n", data_map->ceiling);
	// printf("map =\n");
	// f_print_tab(data_map->map);
	printf("=\n");
	printf("---------data_map out------------\n");
}


void	f_print_tab(char **cou) //TODO a supprimer
{
	int i;

	i = 0;
	while (cou[i])
	{
		printf("%s\n", cou[i]);
		i++;
	}
}

void	*f_freenull(void *str)
{
	if (str)
		free(str);
	return (NULL);
}

void	f_print_file(char *file)
{
	char *str;
	int fd;
	int i = 0;

	fd = open(file, O_RDONLY);

	str = get_next_line(fd);
	while (str)
	{
		if (ft_strlen(str) > 1 && str[ft_strlen(str)] != '\n')
		{
			printf("%s", str);
			i++;
		}
		f_freenull(str);
		str = get_next_line(fd);
	}
	f_freenull(str);
	close(fd);
	printf ("nb line %d\n", i);
}

char	*f_join_and_free(char *src, char *add)
{
	char *res;
	int len_src;
	int len_add;

	len_src = ft_strlen(src);
	len_add = ft_strlen(add);
	res = ft_calloc(sizeof(char), (len_src + len_add + 1));
	if (!res)
		return (res = f_freenull(res));
	while (len_src + len_add-- > len_src)
		res[len_src + len_add] = add[len_add];
	while (len_src--)
		res[len_src] = src[len_src];
	if (*res == 0)
		res = f_freenull(res);
	src = f_freenull(src);
	return (res);
}

char **f_extract_data(char *file)
{
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
	return (map_file);
}

bool f_its_here(char *src, char *search)
{
	int i;

	i = 0;
	while (src[i] <= 32)
		i++;
	if (ft_strncmp(&src[i], search, ft_strlen(search)) == 0)
		return (true);
	return (false);
}



/*A travailler*/
t_dm *f_get_good_map(char **dat)
{
	t_dm	*data_map;
	int i;
	// int j;

	i = -1;
	data_map = ft_calloc(sizeof(t_dm), 1);
	ft_bzero(data_map, sizeof(t_dm));

	while (dat[++i])
	{
		if (f_its_here(dat[i], "NO"))
			data_map->no = ft_strdup(dat[i]);
		else if (f_its_here(dat[i], "SO"))
			data_map->so = ft_strdup(dat[i]);
		else if (f_its_here(dat[i], "WE"))
			data_map->we = ft_strdup(dat[i]);
		else if (f_its_here(dat[i], "EA"))
			data_map->ea = ft_strdup(dat[i]);
		else if (f_its_here(dat[i], "F"))
			data_map->floor = ft_strdup(dat[i]);
		else if (f_its_here(dat[i], "C"))
			data_map->ceiling = ft_strdup(dat[i]);
	}
	return (data_map);
}