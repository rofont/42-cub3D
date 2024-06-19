/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:15:31 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 10:59:28 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_player	*f_init_player(void)
{
	t_player	*play;

	play = ft_calloc(sizeof(t_player), 1);
	return (play);
}

bool	f_is_position(char c)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

char	**f_copy_tab(char **src)
{
	char	**temp;
	int		i;

	i = 0;
	while (src[i])
		i++;
	temp = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (src[++i])
		temp[i] = ft_strdup(src[i]);
	return (temp);
}

void	*f_free_tmap(t_map *data)
{
	if (data)
	{
		if (data->no)
			data->no = f_freenull(data->no);
		if (data->so)
			data->so = f_freenull(data->so);
		if (data->we)
			data->we = f_freenull(data->we);
		if (data->ea)
			data->ea = f_freenull(data->ea);
		if (data->map)
			ft_free_tab_char(data->map);
		data->floor = 0;
		data->ceiling = 0;
		data->map_width = 0;
		data->map_height = 0;
	}
	if (data)
		free(data);
	return (NULL);
}

void	*f_free_player(t_player *play)
{
	play->orientation = 0;
	play->x = 0;
	play->y = 0;
	if (play)
		free(play);
	return (NULL);
}
