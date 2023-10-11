#include "../cube.h"

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
		hit = data->ray->posY + data->ray->perpWallDist \
			* data->ray->rayDirY;
	else
		hit = data->ray->posX + data->ray->perpWallDist \
			* data->ray->rayDirX;
	hit -= (int)hit;
	data->ray->tex_x = (int)(hit * (double)texture->texture.width);
	if ((data->ray->side == 0 || data->ray->side == 1) && data->ray->rayDirX > 0)
		data->ray->tex_x = texture->texture.width - data->ray->tex_x - 1;
	if ((data->ray->side == 2 || data->ray->side == 3) && data->ray->rayDirY < 0)
		data->ray->tex_x = texture->texture.width - data->ray->tex_x - 1;
}


void	draw_texture(t_data *data, int x, xpm_t *wall_tex, int **array)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		i;

	dist = 1.0 * wall_tex->texture.height / data->ray->lineHeight ;
	pos = ((double)data->ray->drawStart - (double)HEIGHT * 0.5 + \
			(double)data->ray->lineHeight * 0.5) * dist;
	if (pos < 0)
		pos = 0;
	i = data->ray->drawStart;
	while (i < data->ray->drawEnd)
	{
		tex_y = (int)pos;
		if (pos > wall_tex->texture.height - 1)
			pos = wall_tex->texture.height - 1;
		pos += dist;
		mlx_put_pixel(data->canvas, x, i++, array[tex_y][data->ray->tex_x]);
	}
}

int	**fill_texture(xpm_t *texture)
{
	int	**array;
	int	i;
	int	j;

	array = ft_calloc(sizeof(int *), texture->texture.height + 1);
	i = 3;
	while (++i < (int) texture->texture.height + 4)
	{
		j = 3;
		array[i - 4] = ft_calloc(texture->texture.width, sizeof(int));
		while (++j < (int) texture->texture.width + 4)
		{
			array[i - 4][j - 4] = get_rgba(
					texture->texture.pixels[(texture->texture.width * 4 \
						* (i - 4)) + (4 * (j - 4)) + 0],
					texture->texture.pixels[(texture->texture.width * 4 \
						* (i - 4)) + (4 * (j - 4)) + 1],
					texture->texture.pixels[(texture->texture.width * 4 \
						* (i - 4)) + (4 * (j - 4)) + 2],
					texture->texture.pixels[(texture->texture.width * 4 \
					* (i - 4)) + (4 * (j - 4)) + 3]);
		}
	}
	return (array);
}