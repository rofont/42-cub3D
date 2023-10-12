/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:16:56 by rofontai          #+#    #+#             */
/*   Updated: 2023/09/25 11:41:47 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_free_tab_char(char **tabl)
{
	size_t	i;

	i = -1;
	while (tabl[++i])
		free(tabl[i]);
	free(tabl);
	return (0);
}
