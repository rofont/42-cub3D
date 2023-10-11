/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:15:51 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/11 19:15:52 by bmartin          ###   ########.fr       */
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
	if (!f_is_good_data(map))
		f_error(E_FILE_NAME, map);
	map->map = ft_calloc(sizeof(char *), size - i + 1);
	while (dat[i])
		map->map[j++] = ft_strdup(dat[i++]);
	dat = NULL;
}

void	f_while_pars(int *i, char **dat, t_map *map)
{
	while (dat[*i])
	{
		if (f_its_here(dat[*i], "NO"))
			map->no = f_pars_direction(dat[*i], "NO");
		else if (f_its_here(dat[*i], "SO"))
			map->so = f_pars_direction(dat[*i], "SO");
		else if (f_its_here(dat[*i], "WE"))
			map->we = f_pars_direction(dat[*i], "WE");
		else if (f_its_here(dat[*i], "EA"))
			map->ea = f_pars_direction(dat[*i], "EA");
		else if (f_its_here(dat[*i], "F"))
			map->floor = f_return_colors(dat[*i], "F");
		else if (f_its_here(dat[*i], "C"))
			map->ceiling = f_return_colors(dat[*i], "C");
		else
			break ;
		*i += 1;
	}
}
