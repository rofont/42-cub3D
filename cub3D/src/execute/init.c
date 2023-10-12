/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:27 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/11 19:07:47 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_data	*get_data(void)

{
	static t_data	*var = NULL;

	if (!var)
	{
		var = ft_calloc(1, sizeof(t_data));
		var->ray = ft_calloc(1, sizeof(t_ray));
		var->player = ft_calloc(1, sizeof(t_player));
		var->map = ft_calloc(1, sizeof(t_map));
		var->tex = ft_calloc(1, sizeof(t_tex));
		return (var);
	}
	return (var);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!(data->mlx))
	{
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	data->canvas = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->canvas, 0, 0);
}

void	init_dir(t_data *data)
{
	data->ray->pos_x = data->player->x + 0.5;
	data->ray->pos_y = data->player->y + 0.5;
	if (data->player->orientation == 'N')
	{
		data->ray->dir_x = -1;
		data->ray->plane_y = 0.66;
	}
	if (data->player->orientation == 'S')
	{
		data->ray->dir_x = 1;
		data->ray->plane_y = -0.66;
	}
	if (data->player->orientation == 'E')
	{
		data->ray->dir_y = 1;
		data->ray->plane_x = 0.66;
	}
	if (data->player->orientation == 'W')
	{
		data->ray->dir_y = -1;
		data->ray->plane_x = -0.66;
	}
}

void	get_texture(t_data *data)
{
	data->tex->no_tex = mlx_load_xpm42(data->map->no);
	data->tex->so_tex = mlx_load_xpm42(data->map->so);
	data->tex->ea_tex = mlx_load_xpm42(data->map->ea);
	data->tex->we_tex = mlx_load_xpm42(data->map->we);
	data->tex->no = fill_texture(data->tex->no_tex);
	data->tex->so = fill_texture(data->tex->so_tex);
	data->tex->we = fill_texture(data->tex->we_tex);
	data->tex->ea = fill_texture(data->tex->ea_tex);
}
