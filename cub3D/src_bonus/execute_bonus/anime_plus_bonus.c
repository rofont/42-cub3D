/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anime_plus_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:08:11 by rofontai          #+#    #+#             */
/*   Updated: 2023/10/13 16:12:36 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int	**free_2d_array(int **array)
{
	int	i;

	if (array == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	make_frame_no(t_data *data, char *text)
{
	mlx_delete_xpm42(data->tex->no_tex);
	data->tex->no_tex = mlx_load_xpm42(text);
	data->tex->no = free_2d_array(data->tex->no);
	data->tex->no = fill_texture(data->tex->no_tex);
}

void	make_frame_so(t_data *data, char *text)
{
	mlx_delete_xpm42(data->tex->so_tex);
	data->tex->so_tex = mlx_load_xpm42(text);
	data->tex->so = free_2d_array(data->tex->so);
	data->tex->so = fill_texture(data->tex->so_tex);
}

void	make_frame_ea(t_data *data, char *text)
{
	mlx_delete_xpm42(data->tex->ea_tex);
	data->tex->ea_tex = mlx_load_xpm42(text);
	data->tex->ea = free_2d_array(data->tex->ea);
	data->tex->ea = fill_texture(data->tex->ea_tex);
}

void	make_frame_we(t_data *data, char *text)
{
	mlx_delete_xpm42(data->tex->we_tex);
	data->tex->we_tex = mlx_load_xpm42(text);
	data->tex->we = free_2d_array(data->tex->we);
	data->tex->we = fill_texture(data->tex->we_tex);
}
