#include "../cube.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	f_is_digit(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (false);
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
	return (true);
}

int	f_search_player(t_map *data, t_player *player)
{
	int	x;
	int	y;
	int	nb_player;

	x = 0;
	nb_player = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (f_is_position(data->map[x][y]))
			{
				player->x = x;
				player->y = y;
				player->orientation = data->map[x][y];
				nb_player++;
			}
			y++;
		}
		x++;
	}
	return (nb_player);
}

void	f_size_maps(t_map *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (cub->map[x])
	{
		y = 0;
		while (cub->map[x][y])
			y++;
		if (cub->map_width < y)
			cub->map_width = y;
		x++;
	}
	cub->map_height = x;
}

void	f_flood_fill(char **temp, t_map *cub, int x, int y)
{
	if (!temp[x] || x < 0 || x > cub->map_height || y < 0 || y
		+ 1 > (int)ft_strlen(temp[x]) || (ft_isdigit(temp[x][y]) && temp[x][y] > '1') ||  temp[x][y] == ' ')
		f_error(E_FLOODFILL, cub);
	if (temp[x][y] == '0' || f_is_position(temp[x][y]))
		temp[x][y] = '.';
	else
		return ;
	f_pri_map(temp); //TODO a supp
	f_flood_fill(temp, cub, x + 1, y);
	f_flood_fill(temp, cub, x - 1, y);
	f_flood_fill(temp, cub, x, y + 1);
	f_flood_fill(temp, cub, x, y - 1);
}
