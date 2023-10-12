/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:21:03 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 12:41:14 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	*play_audio(void *arg)
{
	system("afplay russian.wav");
	return (arg);
}

void	ft_hook(void *param)
{
	t_data	*data;

	(void)param;
	data = get_data();
	player_control(data);
	draw_floor(data);
	draw_sky(data);
	data->anim_f++;
	if (data->anim_f > 60)
		data->anim_f = 0;
	load_dancer(data);
	raycast(data);
	data->scale_factor = 5;
	data->i = 0;
	draw_minimap(data);
	draw_filled_circle(data->canvas, data->ray->pos_y * 5, data->ray->pos_x * 5,
		5);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	thread;
	int			result;

	if (ac != 2)
	{
		ft_putstr_fd(E_ARG, 2);
		exit(1);
	}
	data = get_data();
	init_mlx(data);
	f_pars_file(ac, av, data);
	init_dir(data);
	get_texture(data);
	if (data->map->map_height > 102 || data->map->map_width > 102)
	{
		ft_putstr_fd(E_MAP_TOO_BIG, 2);
		exit(1);
	}
	result = pthread_create(&thread, NULL, play_audio, NULL);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data->mlx, mouse_view_rotation, NULL);
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
