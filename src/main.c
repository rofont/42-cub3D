/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:21:03 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/11 18:27:01 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_hook(void *param)
{
	t_data	*data;

	(void)param;
	data = get_data();
	player_control(data);
	draw_floor_sky(data);
	raycast(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		printf("ERROR good usage = ./cub3d map/path/here\n");
		return (0);
	}
	data = get_data();
	init_mlx(data);
	f_pars_file(ac, av, data);
	init_dir(data);
	get_texture(data);
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
