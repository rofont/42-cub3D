/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:24 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/11 18:28:47 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
				mlx_put_pixel(image, x, y, ft_color(255, 0, 0, 255));
			}
			y++;
		}
		x++;
	}
}

void	draw_floor_sky(t_data *data)
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
			x++;
		}
		x = 0;
		y++;
	}
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
