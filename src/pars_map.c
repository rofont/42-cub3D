#include "cube.h"

void	f_print_player(t_player *play)
{
	printf("x =%d=\n", play->x);
	printf("y =%d=\n", play->y);
	printf("orientation =%c\n", play->orientation);
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
