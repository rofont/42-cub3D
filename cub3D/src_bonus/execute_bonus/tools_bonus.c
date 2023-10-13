/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:36 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/13 15:36:18 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

//put black pixel everywhere
void	reset_window(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(data->canvas, x, y, ft_color(0, 0, 0, 255));
			y++;
		}
		x++;
	}
}

uint32_t	ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	else
		return (0);
}

void	f_free_tex(t_tex *tex)
{
	if (tex)
	{
		if(tex->no)
			tex->no = free_2d_array(tex->no);
		if(tex->so)
			tex->so = free_2d_array(tex->so);
		if(tex->ea)
			tex->ea = free_2d_array(tex->ea);
		if(tex->we)
			tex->we = free_2d_array(tex->we);
		if(tex->no_tex)
			mlx_delete_xpm42(tex->no_tex);
		if(tex->so_tex)
			mlx_delete_xpm42(tex->so_tex);
		if(tex->ea_tex)
			mlx_delete_xpm42(tex->ea_tex);
		if(tex->we_tex)
			mlx_delete_xpm42(tex->we_tex);
		free(tex);
	}
}

void	f_exit_all(t_data *data)
{
	if (data->map)
		f_free_tmap(data->map);
	if (data->player)
		f_free_player(data->player);
	if(data->ray)
	{
		ft_bzero(data->ray, sizeof(t_ray));
		free(data->ray);
	}
	if (data->tex)
		f_free_tex(data->tex);
	if (data)
		free(data);
}
