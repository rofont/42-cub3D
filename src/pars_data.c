#include "cube.h"

char *f_pars_direction(char *line, char *dir)
{
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
	return (res);
}

char	*f_pars_colors(char *line, char *dir)
{
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
	return (color);
}

