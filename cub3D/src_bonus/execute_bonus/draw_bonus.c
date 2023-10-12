/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:24 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 14:36:40 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	draw_filled_circle(mlx_image_t *image, int centerX, int centerY,
		int radius)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = centerX - radius;
	while (x <= centerX + radius && x <= WIDTH - radius)
	{
		y = centerY - radius;
		while (y <= centerY + radius && y <= HEIGHT - radius)
		{
			dx = x - centerX;
			dy = y - centerY;
			if (dx * dx + dy * dy <= radius * radius)
			{
				mlx_put_pixel(image, x + 10, y + 10, ft_color(255, 0, 0, 255));
			}
			y++;
		}
		x++;
	}
}

void	draw_sky(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		while (x < WIDTH)
		{
			mlx_put_pixel(data->canvas, x, y, data->map->ceiling);
			data->map->ceiling++;
			data->map->floor++;
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mlx_put_pixel(data->canvas, x, y, data->map->floor);
			x++;
		}
		x = 0;
		y++;
	}
}

uint32_t	get_color(char map_element)
{
	if (map_element == '0')
		return (ft_color(255, 255, 255, 255));
	else if (map_element == '1')
		return (ft_color(0, 0, 0, 255));
	else
		return (ft_color(0, 0, 0, 100));
}

void	draw_minimap(t_data *data)
{
	while (data->i < data->map->map_height)
	{
		data->j = 0;
		while (data->j < data->map->map[data->i][data->j])
		{
			data->color = get_color(data->map->map[data->i][data->j]);
			data->start_x = data->j * data->scale_factor;
			data->start_y = data->i * data->scale_factor;
			data->x = data->start_x;
			while (data->x < data->start_x + data->scale_factor)
			{
				data->y = data->start_y;
				while (data->y < data->start_y + data->scale_factor)
				{
					mlx_put_pixel(data->canvas, data->x + 10, data->y + 10,
						data->color);
					data->y++;
				}
				data->x++;
			}
			data->j++;
		}
		data->i++;
	}
}
