/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:20 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/11 18:28:56 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	player_control(t_data *data)
{
	data->player->move_speed = 0.1;
	data->player->rot_speed = 0.05;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, 'w');
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, 's');
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		strafe_player(data, 'a');
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		strafe_player(data, 'd');
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player_r(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player_l(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		exit(0);
	}
}

void	move_player(t_data *data, char key)
{
	double	new_x;
	double	new_y;
	double	col_buffer;

	new_x = data->ray->pos_x;
	new_y = data->ray->pos_y;
	col_buffer = 0.001;
	if (key == 'w')
	{
		new_x += data->ray->dir_x * data->player->move_speed + col_buffer;
		new_y += data->ray->dir_y * data->player->move_speed + col_buffer;
	}
	else if (key == 's')
	{
		new_x -= data->ray->dir_x * data->player->move_speed + col_buffer;
		new_y -= data->ray->dir_y * data->player->move_speed + col_buffer;
	}
	if (data->map->map[(int)new_x][(int)new_y] == '0'
		|| is_player(data->map->map[(int)new_x][(int)new_y]))
	{
		data->ray->pos_x = new_x;
		data->ray->pos_y = new_y;
	}
}

void	strafe_player(t_data *data, char direction)
{
	double	leftdir_x;
	double	leftdir_y;
	double	new_x;
	double	new_y;

	leftdir_x = -data->ray->dir_y;
	leftdir_y = data->ray->dir_x;
	new_x = data->ray->pos_x;
	new_y = data->ray->pos_y;
	if (direction == 'a')
	{
		new_x += leftdir_x * data->player->move_speed + 0.001;
		new_y += leftdir_y * data->player->move_speed + 0.001;
	}
	else if (direction == 'd')
	{
		new_x -= leftdir_x * data->player->move_speed + 0.001;
		new_y -= leftdir_y * data->player->move_speed + 0.001;
	}
	if (data->map->map[(int)new_x][(int)new_y] == '0'
		|| is_player(data->map->map[(int)new_x][(int)new_y]))
	{
		data->ray->pos_x = new_x;
		data->ray->pos_y = new_y;
	}
}

void	rotate_player_l(t_data *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->ray->dir_x;
	oldplane_x = data->ray->plane_x;
	data->ray->dir_x = data->ray->dir_x * cos(data->player->rot_speed)
		- data->ray->dir_y * sin(data->player->rot_speed);
	data->ray->dir_y = olddir_x * sin(data->player->rot_speed)
		+ data->ray->dir_y * cos(data->player->rot_speed);
	data->ray->plane_x = data->ray->plane_x * cos(data->player->rot_speed)
		- data->ray->plane_y * sin(data->player->rot_speed);
	data->ray->plane_y = oldplane_x * sin(data->player->rot_speed)
		+ data->ray->plane_y * cos(data->player->rot_speed);
}

void	rotate_player_r(t_data *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->ray->dir_x;
	oldplane_x = data->ray->plane_x;
	data->ray->dir_x = data->ray->dir_x * cos(-data->player->rot_speed)
		- data->ray->dir_y * sin(-data->player->rot_speed);
	data->ray->dir_y = olddir_x * sin(-data->player->rot_speed)
		+ data->ray->dir_y * cos(-data->player->rot_speed);
	data->ray->plane_x = data->ray->plane_x * cos(-data->player->rot_speed)
		- data->ray->plane_y * sin(-data->player->rot_speed);
	data->ray->plane_y = oldplane_x * sin(-data->player->rot_speed)
		+ data->ray->plane_y * cos(-data->player->rot_speed);
}
