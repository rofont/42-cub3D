#include "cube.h"

void	f_print_player(t_player *play)
{
	printf("x =%d=\n", play->x);
	printf("y =%d=\n", play->y);
	printf("orientation =%c=\n", play->orientation);
}

void	f_print_map(t_map *play)
{
	printf("height =%d=\n", play->map_height);
	printf("width =%d=\n", play->map_width);
	printf("map = \n");
	f_print_tab(play->map);
}

t_player	*f_init_player(t_player *play)
{
	play = ft_calloc(sizeof(t_player), 1);
	return (play);
}

bool	f_is_position(char c)
{
	if(c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

int	f_search_player(t_dm *data, t_player *player)
{
	if (DEBUG == 1)
		printf(CYA"-----search_player in-----\n"WHT);
	int x;
	int y;
	int nb_player;
	x = 0;
	nb_player = 0;

	(void)player;
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

t_map	*f_maps(t_map *cub, t_dm *data)
{
	int x;
	int y;

	if (DEBUG == 1)
		printf(CYA"-----maps in-----\n"WHT);
	x = 0;
	y =0;
	cub = ft_calloc(sizeof(t_map), 1);
	while(data->map[x])
	{
		y = 0;
		while(data->map[x][y])
			y++;
		if (cub->map_width < y)
			cub->map_width = y;
		x++;
	}
	cub->map_height = x;
	if (DEBUG == 1)
		printf(GRE"-----maps out-----\n"WHT);
	return (cub);
}

void f_modif_map(t_map *cub, t_dm *data)
{
	int x;
	int y;

	if (DEBUG == 1)
		printf(CYA"-----modif_map in-----\n"WHT);
	x = 0;
	cub->map = ft_calloc(sizeof(char *), cub->map_height + 1);
	while(x < cub->map_height)
	{
		y = 0;
		cub->map[x] = ft_calloc(sizeof(char), cub->map_width + 1);
		while(y < cub->map_width)
		{
			if (ft_strlen(data->map[x]) < (size_t)cub->map_width && (size_t)y > ft_strlen(data->map[x]))
				cub->map[x][y] = 'y';
			else if (data->map[x][y] == '1' || data->map[x][y] == '0' || f_is_position(data->map[x][y]))
				cub->map[x][y] = data->map[x][y];
			else
				cub->map[x][y] = 'y';
			y++;
		}
		x++;
	}
	if (DEBUG == 1)
		printf(GRE"-----modif_map out-----\n"WHT);
}

void	f_flood_fill(t_map *cub, int x, int y, int x1, int y1)
{
	// if (DEBUG == 1)
	// 	printf(CYA"-----flood in-----\n"WHT);
	if (x < 0 || x > x1 || y < 0 || y > y1)
		return ;
	if (cub->map[x][y] == '1' || cub->map[x][y] == 'y' || cub->map[x][y] == 'x')
		return ;
	if (cub->map[x][y] == '0')
	{

	}
		cub->map[x][y] = 'x';
	f_flood_fill(cub, x, y + 1, x1, y1);
	f_flood_fill(cub, x, y - 1, x1, y1);
	f_flood_fill(cub, x + 1, y, x1, y1);
	f_flood_fill(cub, x - 1, y, x1, y1);
	// if (DEBUG == 1)
		// printf(CYA"-----flood out-----\n"WHT);
}