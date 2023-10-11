#include "../cube.h"

int	f_number(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		nb = (nb * 10) + (str[i++] - 48);
	if (nb < 0 || nb > 255)
		return (-1);
	return (nb);
}

int	f_return_colors(char *line, char *dir, t_map *data)
{
	char	*temp;
	int		*tab;
	int		res;

	temp = f_pars_colors(line, dir);
	tab = f_tab_color(temp, data);
	res = get_rgba(tab[0], tab[1], tab[2], 100);
	temp = f_freenull(temp);
	free(tab);
	return (res);
}

int	*f_tab_color(char *line, t_map *data)
{
	char	**tab_char;
	int		*tab;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tab = ft_calloc(sizeof(int), 3);
	tab_char = ft_split(line, ',');
	while (tab_char[i] || j == 4)
	{
		if (!f_is_digit(tab_char[i]) || f_number(tab_char[i]) == -1)
			f_error(E_COLORS, data);
		tab[j++] = f_number(tab_char[i++]);
	}
	ft_free_tab_char(tab_char);
	if (i != 3)
		f_error(E_COLORS, data);
	return (tab);
}

char	*f_pars_colors(char *line, char *dir)
{
	char	*color;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (line[i] <= 32)
		i++;
	if (line[i] == '\0')
		return (NULL);
	temp = ft_strtrim(&line[i], dir);
	color = ft_calloc(sizeof(char), ft_strlen(temp));
	i = 0;
	while (temp[i])
	{
		if (temp[i] <= 32)
			i++;
		else
			color[j++] = temp[i++];
	}
	temp = f_freenull(temp);
	return (color);
}

int f_is_good_data(t_map *map)
{
	if (map->no == NULL)
		return (-1);
	if (map->so == NULL)
		return (-1);
	if (map->we == NULL)
		return (-1);
	if (map->ea == NULL)
		return (-1);
	if (map->ceiling == 0)
		return (-2);
	if (map->floor == 0)
		return (-2);
	return (0);
}
