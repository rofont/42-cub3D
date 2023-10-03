#include "cube.h"

int	f_search_player(t_map *data, t_player *player)
{
	if (DEBUG == 1)
		printf(CYA"-----search_player in-----\n"WHT);
	int x;
	int y;
	int nb_player;

	x = 0;
	nb_player = 0;
	while(data->map[x])
	{
		y = 0;
		while(data->map[x][y])
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
	if (DEBUG == 1)
		printf(GRE"-----search_player out-----\n"WHT);
	return (nb_player);
}

void	f_size_maps(t_map *cub)
{
	int x;
	int y;

	if (DEBUG == 1)
		printf(CYA"-----maps in-----\n"WHT);
	x = 0;
	y =0;
	while(cub->map[x])
	{
		y = 0;
		while(cub->map[x][y])
			y++;
		if (cub->map_width < y)
			cub->map_width = y;
		x++;
	}
	cub->map_height = x;
	if (DEBUG == 1)
		printf(GRE"-----maps out-----\n"WHT);
}

void	f_flood_fill(char **temp, t_map *cub, int x, int y)
{
	if (!temp[x] || x < 0 || x > cub->map_height || y < 0 || y + 1 > (int)ft_strlen(temp[x]) || temp[x][y] == ' ')
		f_error(E_FLOODFILL);
	if (temp[x][y] == '0' || f_is_position(temp[x][y]))
		temp[x][y] = '.';
	else
		return;
	f_pri_map(temp);
	f_flood_fill(temp, cub, x + 1, y);
	f_flood_fill(temp, cub, x - 1, y);
	f_flood_fill(temp, cub, x, y + 1);
	f_flood_fill(temp, cub, x, y - 1);
}