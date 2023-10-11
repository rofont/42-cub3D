/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:30 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/11 18:20:31 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	raycast(t_data *data)
{
	data->ray->i = 0;
	while (data->ray->i < WIDTH)
	{
		ray_init(data);
		get_side_dist(data);
		dda(data);
		get_wall(data);
		choose_texture(data, data->ray->i);
		data->ray->i++;
	}
}

void	ray_init(t_data *data)
{
	data->ray->camera_x = 2 * data->ray->i / (double)WIDTH - 1;
	data->ray->raydir_x = data->ray->dir_x + data->ray->plane_x
		* data->ray->camera_x;
	data->ray->raydir_y = data->ray->dir_y + data->ray->plane_y
		* data->ray->camera_x;
	data->ray->map_x = (int)data->ray->pos_x;
	data->ray->map_y = (int)data->ray->pos_y;
	data->ray->delta_dist_x = fabs(1 / data->ray->raydir_x);
	data->ray->delta_dist_y = fabs(1 / data->ray->raydir_y);
}

void	get_side_dist(t_data *data)
{
	if (data->ray->raydir_x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_dist_x = (data->ray->pos_x - data->ray->map_x)
			* data->ray->delta_dist_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->ray->map_x + 1.0 - data->ray->pos_x)
			* data->ray->delta_dist_x;
	}
	if (data->ray->raydir_y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->ray->pos_y - data->ray->map_y)
			* data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = (data->ray->map_y + 1.0 - data->ray->pos_y)
			* data->ray->delta_dist_y;
	}
}

void	dda(t_data *data)
{
	data->ray->hit = 0;
	while (!data->ray->hit)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->ray->map_x += data->ray->step_x;
			if (data->ray->raydir_x >= 0)
				data->ray->side = 0;
			else
				data->ray->side = 1;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->ray->map_y += data->ray->step_y;
			if (data->ray->raydir_y > 0)
				data->ray->side = 2;
			else
				data->ray->side = 3;
		}
		if (data->map->map[data->ray->map_x][data->ray->map_y] == '1')
			data->ray->hit = 1;
	}
}

void	get_wall(t_data *data)
{
	if (data->ray->side == 0 || data->ray->side == 1)
		data->ray->perp_wall_dist = (data->ray->map_x - data->ray->pos_x + (1
					- data->ray->step_x) / 2) / data->ray->raydir_x;
	else
		data->ray->perp_wall_dist = (data->ray->map_y - data->ray->pos_y + (1
					- data->ray->step_y) / 2) / data->ray->raydir_y;
	data->ray->line_height = (int)(HEIGHT / data->ray->perp_wall_dist);
	data->ray->draw_start = -data->ray->line_height / 2 + HEIGHT / 2;
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0;
	data->ray->draw_end = data->ray->line_height / 2 + HEIGHT / 2;
	if (data->ray->draw_end >= HEIGHT)
		data->ray->draw_end = HEIGHT - 1;
}
