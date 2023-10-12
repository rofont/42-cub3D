/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:15:51 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 12:20:10 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// transforme le fichier en char **
char	**f_extract_data(char *file)
{
	int		fd;
	char	*temp;
	char	*line;
	char	**map_file;

	temp = "pouet";
	line = NULL;
	fd = open(file, O_RDONLY);
	while (temp)
	{
		temp = get_next_line(fd);
		line = f_join_and_free(line, temp);
		f_freenull(temp);
	}
	close(fd);
	map_file = ft_split(line, '\n');
	line = f_freenull(line);
	return (map_file);
}

// extrait les données corectement et check si elle sont dans le bon ordre
void	f_get_data(t_map *map, char **dat)
{
	int	size;
	int	i;
	int	j;

	size = 0;
	i = 0;
	j = 0;
	while (dat[size])
		size++;
	f_while_pars(&i, dat, map);
	if (f_is_good_data(map) == -2)
		f_error(E_COLORS, map);
	if (f_is_good_data(map) == -1)
		f_error(E_ASSET, map);
	map->map = ft_calloc(sizeof(char *), size - i + 1);
	while (dat[i])
		map->map[j++] = ft_strdup(dat[i++]);
	dat = NULL;
}

void	f_while_pars(int *i, char **dat, t_map *map)
{
	while (dat[*i])
	{
		if (!map->no && f_its_here(dat[*i], "NO"))
			map->no = f_pars_direction(dat[*i], "NO");
		else if (!map->so && f_its_here(dat[*i], "SO"))
			map->so = f_pars_direction(dat[*i], "SO");
		else if (!map->we && f_its_here(dat[*i], "WE"))
			map->we = f_pars_direction(dat[*i], "WE");
		else if (!map->ea && f_its_here(dat[*i], "EA"))
			map->ea = f_pars_direction(dat[*i], "EA");
		else if (!map->floor && f_its_here(dat[*i], "F"))
			map->floor = f_return_colors(dat[*i], "F", map);
		else if (!map->ceiling && f_its_here(dat[*i], "C"))
			map->ceiling = f_return_colors(dat[*i], "C", map);
		else
			break ;
		*i += 1;
	}
}

bool	f_check_ascii_map(char c)
{
	if (c == ' ' || c == '1' || c == '0' || f_is_position(c))
		return (true);
	return (false);
}

bool	f_check_map_good(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (data->map->map[++i])
	{
		j = 0;
		while (data->map->map[i][j] && f_check_ascii_map(data->map->map[i][j]))
			j++;
		if (data->map->map[i][j] != '\0')
			return (false);
	}
	return (true);
}
