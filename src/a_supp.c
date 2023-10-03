#include "cube.h"

void	f_print_tab(char **cou) //TODO a supprimer
{
	int i;

	i = 0;
	while (cou[i])
	{
		printf("%s\n", cou[i]);
		i++;
	}
}

void	f_print_map(t_map *data_map)
{
	printf("---------data_map in------------\n");
	printf("NO =%s=\n", data_map->no);
	printf("SO =%s=\n", data_map->so);
	printf("WE =%s=\n", data_map->we);
	printf("EA =%s=\n", data_map->ea);
	printf("F =%d=\n", data_map->floor);
	printf("C =%d=\n", data_map->ceiling);
	printf("height =%d=\n", data_map->map_height);
	printf("width =%d=\n", data_map->map_width);
	printf("map =\n");
	f_print_tab(data_map->map);
	printf("=\n");

	printf("---------data_map out------------\n");
}

void	f_pri_map(char **map)
{
	int	i;

	i = 0;
	usleep(50000);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	f_print_player(t_player *play)
{
	printf("x =%d=\n", play->x);
	printf("y =%d=\n", play->y);
	printf("orientation =%c=\n", play->orientation);
}