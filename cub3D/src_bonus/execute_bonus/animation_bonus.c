/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:20 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 14:36:30 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	load_dancer(t_data *data)
{
	load_no(data);
	load_so(data);
	load_ea(data);
	load_we(data);
}

void	load_no(t_data *data)
{
	if (data->anim_f > 0 && data->anim_f < 12)
	{
		data->tex->no_tex = mlx_load_xpm42("./texture/dancer/dj1.xpm42");
		data->tex->no = fill_texture(data->tex->no_tex);
	}
	if (data->anim_f > 12 && data->anim_f < 24)
	{
		data->tex->no_tex = mlx_load_xpm42("./texture/dancer/dj2.xpm42");
		data->tex->no = fill_texture(data->tex->no_tex);
	}
	if (data->anim_f > 24 && data->anim_f < 36)
	{
		data->tex->no_tex = mlx_load_xpm42("./texture/dancer/dj3.xpm42");
		data->tex->no = fill_texture(data->tex->no_tex);
	}
	if (data->anim_f > 36 && data->anim_f < 48)
	{
		data->tex->no_tex = mlx_load_xpm42("./texture/dancer/dj4.xpm42");
		data->tex->no = fill_texture(data->tex->no_tex);
	}
	if (data->anim_f > 48 && data->anim_f < 60)
	{
		data->tex->no_tex = mlx_load_xpm42("./texture/dancer/dj5.xpm42");
		data->tex->no = fill_texture(data->tex->no_tex);
	}
}

void	load_so(t_data *data)
{
	data->map->floor++;
	if (data->anim_f > 0 && data->anim_f < 15)
	{
		data->tex->so_tex = mlx_load_xpm42("./texture/dancer/glow1.xpm42");
		data->tex->so = fill_texture(data->tex->so_tex);
	}
	if (data->anim_f > 15 && data->anim_f < 30)
	{
		data->tex->so_tex = mlx_load_xpm42("./texture/dancer/glow2.xpm42");
		data->tex->so = fill_texture(data->tex->so_tex);
	}
	if (data->anim_f > 30 && data->anim_f < 45)
	{
		data->tex->so_tex = mlx_load_xpm42("./texture/dancer/glow3.xpm42");
		data->tex->so = fill_texture(data->tex->so_tex);
	}
	if (data->anim_f > 45 && data->anim_f < 60)
	{
		data->tex->so_tex = mlx_load_xpm42("./texture/dancer/glow4.xpm42");
		data->tex->so = fill_texture(data->tex->so_tex);
	}
}

void	load_ea(t_data *data)
{
	if (data->anim_f > 0 && data->anim_f < 15)
	{
		data->tex->ea_tex = mlx_load_xpm42("./texture/dancer/cat1.xpm42");
		data->tex->ea = fill_texture(data->tex->ea_tex);
	}
	if (data->anim_f > 15 && data->anim_f < 30)
	{
		data->tex->ea_tex = mlx_load_xpm42("./texture/dancer/cat2.xpm42");
		data->tex->ea = fill_texture(data->tex->ea_tex);
	}
	if (data->anim_f > 30 && data->anim_f < 45)
	{
		data->tex->ea_tex = mlx_load_xpm42("./texture/dancer/cat3.xpm42");
		data->tex->ea = fill_texture(data->tex->ea_tex);
	}
	if (data->anim_f > 45 && data->anim_f < 60)
	{
		data->tex->ea_tex = mlx_load_xpm42("./texture/dancer/cat4.xpm42");
		data->tex->ea = fill_texture(data->tex->ea_tex);
	}
}

void	load_we(t_data *data)
{
	if (data->anim_f > 0 && data->anim_f < 15)
	{
		data->tex->we_tex = mlx_load_xpm42("./texture/dancer/party1.xpm42");
		data->tex->we = fill_texture(data->tex->we_tex);
	}
	if (data->anim_f > 15 && data->anim_f < 30)
	{
		data->tex->we_tex = mlx_load_xpm42("./texture/dancer/party2.xpm42");
		data->tex->we = fill_texture(data->tex->we_tex);
	}
	if (data->anim_f > 30 && data->anim_f < 45)
	{
		data->tex->we_tex = mlx_load_xpm42("./texture/dancer/party3.xpm42");
		data->tex->we = fill_texture(data->tex->we_tex);
	}
	if (data->anim_f > 45 && data->anim_f < 60)
	{
		data->tex->we_tex = mlx_load_xpm42("./texture/dancer/party4.xpm42");
		data->tex->we = fill_texture(data->tex->we_tex);
	}
}
