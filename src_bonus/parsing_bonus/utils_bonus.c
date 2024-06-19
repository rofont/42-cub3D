/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:20:49 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 14:37:50 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	*f_freenull(void *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	*f_join_and_free(char *src, char *add)
{
	char	*res;
	int		len_src;
	int		len_add;

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
	t_map	*new;

	new = ft_calloc(sizeof(t_map), 1);
	return (new);
}

bool	f_its_here(char *src, char *search)
{
	int	i;

	i = 0;
	while (src[i] <= 32)
		i++;
	if (ft_strncmp(&src[i], search, ft_strlen(search)) == 0)
		return (true);
	return (false);
}

char	*f_pars_direction(char *line, char *dir)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(char), ft_strlen(line));
	while (line[i] <= 32)
		i++;
	if (line[i] == '\0')
		return (NULL);
	temp = ft_strtrim(&line[i], dir);
	i = 0;
	while (temp[i] <= 32)
		i++;
	if (temp[i] == '\0')
		return (NULL);
	while (temp[i] > 32)
		res[j++] = temp[i++];
	temp = f_freenull(temp);
	return (res);
}
