/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:20 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/13 16:12:41 by rofontai         ###   ########.fr       */
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
		make_frame_no(data, "./texture/dancer/dj1.xpm42");
	if (data->anim_f > 12 && data->anim_f < 24)
		make_frame_no(data, "./texture/dancer/dj2.xpm42");
	if (data->anim_f > 24 && data->anim_f < 36)
		make_frame_no(data, "./texture/dancer/dj3.xpm42");
	if (data->anim_f > 36 && data->anim_f < 48)
		make_frame_no(data, "./texture/dancer/dj4.xpm42");
	if (data->anim_f > 48 && data->anim_f < 60)
		make_frame_no(data, "./texture/dancer/dj5.xpm42");
}

void	load_so(t_data *data)
{
	data->map->floor++;
	if (data->anim_f > 0 && data->anim_f < 12)
		make_frame_so(data, "./texture/dancer/glow1.xpm42");
	if (data->anim_f > 12 && data->anim_f < 24)
		make_frame_so(data, "./texture/dancer/glow2.xpm42");
	if (data->anim_f > 24 && data->anim_f < 36)
		make_frame_so(data, "./texture/dancer/glow3.xpm42");
	if (data->anim_f > 36 && data->anim_f < 48)
		make_frame_so(data, "./texture/dancer/glow4.xpm42");
}

void	load_ea(t_data *data)
{
	if (data->anim_f > 0 && data->anim_f < 12)
		make_frame_ea(data, "./texture/dancer/cat1.xpm42");
	if (data->anim_f > 12 && data->anim_f < 24)
		make_frame_ea(data, "./texture/dancer/cat2.xpm42");
	if (data->anim_f > 24 && data->anim_f < 36)
		make_frame_ea(data, "./texture/dancer/cat3.xpm42");
	if (data->anim_f > 36 && data->anim_f < 48)
		make_frame_ea(data, "./texture/dancer/cat4.xpm42");
}

void	load_we(t_data *data)
{
	if (data->anim_f > 0 && data->anim_f < 12)
		make_frame_we(data, "./texture/dancer/party1.xpm42");
	if (data->anim_f > 12 && data->anim_f < 24)
		make_frame_we(data, "./texture/dancer/party2.xpm42");
	if (data->anim_f > 24 && data->anim_f < 36)
		make_frame_we(data, "./texture/dancer/party3.xpm42");
	if (data->anim_f > 36 && data->anim_f < 48)
		make_frame_we(data, "./texture/dancer/party4.xpm42");
}
