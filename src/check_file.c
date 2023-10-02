#include "cube.h"

void	f_print_dm(t_dm *data_map)
{
	printf("---------data_map in------------\n");
	printf("NO =%s=\n", data_map->no);
	printf("SO =%s=\n", data_map->so);
	printf("WE =%s=\n", data_map->we);
	printf("EA =%s=\n", data_map->ea);
	printf("F =%d=\n", data_map->floor);
	printf("C =%d=\n", data_map->ceiling);
	// printf("map =\n");
	// f_print_tab(data_map->map);
	// printf("=\n");
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

t_dm *f_get_good_map(char **dat)
{
	t_dm	*data_map;
	int i;
	int j;
	int size;

	if (DEBUG == 1)
		printf(CYA"-----get_good_data in-----\n"WHT);
	size = 0;
	j = 0;
	i = -1;
	data_map = ft_calloc(sizeof(t_dm), 1);
	ft_bzero(data_map, sizeof(t_dm));
	while (dat[size])
		size ++;
	while (dat[++i])
	{
		if (f_its_here(dat[i], "NO"))
			data_map->no = f_pars_direction(dat[i], "NO");
		else if (f_its_here(dat[i], "SO"))
			data_map->so = f_pars_direction(dat[i], "SO");
		else if (f_its_here(dat[i], "WE"))
			data_map->we = f_pars_direction(dat[i], "WE");
		else if (f_its_here(dat[i], "EA"))
			data_map->ea = f_pars_direction(dat[i], "EA");
		else if (f_its_here(dat[i], "F"))
			data_map->floor = f_return_colors(dat[i], "F");
		else if (f_its_here(dat[i], "C"))
			data_map->ceiling = f_return_colors(dat[i], "C");
		else
			break ;
	}
	data_map->map = ft_calloc(sizeof(char *), size - i + 1);
	while (dat[i])
		data_map->map[j++] = ft_strdup(dat[i++]);
	if (DEBUG == 1)
		printf(GRE"-----get_good_data out-----\n"WHT);
	return (data_map);
}

void	*f_free_dm(t_dm *data)
{
	if (data->no)
		data->no = f_freenull(data->no);
	if (data->so)
		data->so = f_freenull(data->so);
	if (data->we)
		data->we = f_freenull(data->we);
	if (data->ea)
		data->ea = f_freenull(data->ea);
	data->ceiling = 0;
	data->floor = 0;
	if (data->map)
		ft_free_tab_char(data->map);
	free(data);
	return (NULL);
}