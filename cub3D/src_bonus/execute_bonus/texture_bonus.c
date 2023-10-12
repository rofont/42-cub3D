/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:33 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 14:36:50 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	choose_texture(t_data *data, int x)
{
	if (data->ray->side == 0)
	{
		find_texture(data, data->tex->so_tex);
		draw_texture(data, x, data->tex->so_tex, data->tex->so);
	}
	if (data->ray->side == 1)
	{
		find_texture(data, data->tex->no_tex);
		draw_texture(data, x, data->tex->no_tex, data->tex->no);
	}
	if (data->ray->side == 2)
	{
		find_texture(data, data->tex->ea_tex);
		draw_texture(data, x, data->tex->ea_tex, data->tex->ea);
	}
	if (data->ray->side == 3)
	{
		find_texture(data, data->tex->we_tex);
		draw_texture(data, x, data->tex->we_tex, data->tex->we);
	}
}

void	find_texture(t_data *data, xpm_t *texture)
{
	double	hit;

	hit = 0;
	if (data->ray->side == 0 || data->ray->side == 1)
		hit = data->ray->pos_y + data->ray->perp_wall_dist
			* data->ray->raydir_y;
	else
		hit = data->ray->pos_x + data->ray->perp_wall_dist
			* data->ray->raydir_x;
	hit -= (int)hit;
	data->ray->tex_x = (int)(hit * (double)texture->texture.width);
	if ((data->ray->side == 0 || data->ray->side == 1)
		&& data->ray->raydir_x > 0)
		data->ray->tex_x = texture->texture.width - data->ray->tex_x - 1;
	if ((data->ray->side == 2 || data->ray->side == 3)
		&& data->ray->raydir_y < 0)
		data->ray->tex_x = texture->texture.width - data->ray->tex_x - 1;
}

void	draw_texture(t_data *data, int x, xpm_t *wall_tex, int **array)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		i;

	dist = 1.0 * wall_tex->texture.height / data->ray->line_height;
	pos = ((double)data->ray->draw_start - (double)HEIGHT * 0.5
			+ (double)data->ray->line_height * 0.5) * dist;
	if (pos < 0)
		pos = 0;
	i = data->ray->draw_start;
	while (i < data->ray->draw_end)
	{
		tex_y = (int)pos;
		if (pos > wall_tex->texture.height - 1)
			pos = wall_tex->texture.height - 1;
		pos += dist;
		mlx_put_pixel(data->canvas, x, i++, array[tex_y][data->ray->tex_x]);
	}
}

int	fill_array(xpm_t *texture, int i, int j)
{
	int	color;

	color = get_rgba(
			texture->texture.pixels[(texture->texture.width * 4 * (i - 4))
			+ (4 * (j - 4)) + 0],
			texture->texture.pixels[(texture->texture.width * 4 * (i - 4))
			+ (4 * (j - 4)) + 1],
			texture->texture.pixels[(texture->texture.width * 4 * (i - 4))
			+ (4 * (j - 4)) + 2],
			texture->texture.pixels[(texture->texture.width * 4 * (i - 4))
			+ (4 * (j - 4)) + 3]);
	return (color);
}

int	**fill_texture(xpm_t *texture)
{
	int	**array;
	int	i;
	int	j;

	if (!(texture))
	{
		ft_putstr_fd(E_TEX_PATH, 2);
		exit(1);
	}
	array = ft_calloc(sizeof(int *), texture->texture.height + 1);
	i = 3;
	while (++i < (int)texture->texture.height + 4)
	{
		j = 3;
		array[i - 4] = ft_calloc(texture->texture.width, sizeof(int));
		while (++j < (int)texture->texture.width + 4)
		{
			array[i - 4][j - 4] = fill_array(texture, i, j);
		}
	}
	return (array);
}
