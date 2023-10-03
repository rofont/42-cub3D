#include "cube.h"

void	*f_freenull(void *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	*f_join_and_free(char *src, char *add)
{
	char *res;
	int len_src;
	int len_add;

	len_src = ft_strlen(src);
	len_add = ft_strlen(add);
	res = ft_calloc(sizeof(char), (len_src + len_add + 1));
	if (!res)
		return (res = f_freenull(res));
	while (len_src + len_add-- > len_src)
		res[len_src + len_add] = add[len_add];
	while (len_src--)
		res[len_src] = src[len_src];
	if (*res == 0)
		res = f_freenull(res);
	src = f_freenull(src);
	return (res);
}

t_map	*f_init_map(void)
{
	t_map *new;

	new = ft_calloc(sizeof(t_map), 1);
	return (new);
}

bool	f_its_here(char *src, char *search)
{
	int i;

	i = 0;
	while (src[i] <= 32)
		i++;
	if (ft_strncmp(&src[i], search, ft_strlen(search)) == 0)
		return (true);
	return (false);
}

char	*f_pars_direction(char *line, char *dir)
{
	if (DEBUG == 1)
		printf(CYA"-----pars_direction in-----\n"WHT);
	char *res;
	char *temp;
	int i;
	int j;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(char), ft_strlen(line));
	while(line[i] <= 32)
		i++;
	if (line[i] == '\0')
		return (NULL);
	temp = ft_strtrim(&line[i], dir);
	i = 0;
	while(temp[i] <= 32)
		i++;
	if (temp[i] == '\0')
		return (NULL);
	while (temp[i] > 32)
	res[j++] = temp [i++];
	temp = f_freenull(temp);
	if (DEBUG == 1)
		printf(GRE"-----pars_direction out-----\n"WHT);
	return (res);
}

int get_rgba(int r, int g, int b, int a)
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

int	f_return_colors(char *line, char *dir)
{
	if (DEBUG == 1)
		printf(CYA"-----return_colors in-----\n"WHT);
	char *temp;
	int *tab;
	int res;
	temp = f_pars_colors(line, dir);
	tab = f_tab_color(temp);
	res = get_rgba(tab[0], tab[1], tab[2], 100);
	temp = f_freenull(temp);
	free(tab);
	if (DEBUG == 1)
		printf(GRE"-----return_colors out-----\n"WHT);
	return (res);
}

int	*f_tab_color(char *line)
{
	if (DEBUG == 1)
		printf(CYA"-----tab_color in-----\n"WHT);
	char **tab_char;
	int	*tab;
	int i;
	int j;

	j = 0;
	i = 0;
	tab = ft_calloc(sizeof(int), 3);
	tab_char = ft_split(line, ',');
	while (tab_char[i] || j == 4)
	{
		if (!f_is_digit(tab_char[i]) || f_number(tab_char[i]) == - 1)
			f_error(E_COLORS);
		tab[j++] = f_number(tab_char[i++]);
	}
	ft_free_tab_char(tab_char);
	if (DEBUG == 1)
		printf(GRE"-----tab_color out-----\n"WHT);
	return (tab);
}

char	*f_pars_colors(char *line, char *dir)
{
	if (DEBUG == 1)
		printf(CYA"-----pars_colors in-----\n"WHT);
	char *color;
	int i;
	int j;
	char *temp;

	i = 0;
	j = 0;
	while(line[i] <= 32)
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
			color[j++] = temp [i++];
	}
	temp = f_freenull(temp);
	if (DEBUG == 1)
		printf(GRE"-----pars_colors out-----\n"WHT);
	return (color);
}

bool	f_is_good_data(t_map *map)
{
	if (map->no == NULL)
		return (false);
	if (map->so == NULL)
		return (false);
	if (map->we == NULL)
		return (false);
	if (map->ea == NULL)
		return (false);
	if (map->ceiling == 0)
 		return (false);
	if (map->floor == 0)
		return (false);
	return (true);
}

t_player	*f_init_player(void)
{
	t_player *play;

	play = ft_calloc(sizeof(t_player), 1);
	return (play);
}

bool	f_is_position(char c)
{
	if(c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

char	**f_copy_tab(char **src)
{
	char **temp;
	int i;

	i = 0;
	while (src[i])
		i++;
	temp = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (src[++i])
		temp[i] = ft_strdup(src[i]);
	return (temp);
}
