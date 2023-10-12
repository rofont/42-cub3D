/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:50:33 by bmartin           #+#    #+#             */
/*   Updated: 2023/02/01 18:31:53 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
size_t	ft_strlen2(char *str);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strchr2(char *s, int c);
char	*ft_substr_overflow(char *s);
void	*ft_calloc2(size_t nitems, size_t size);
char	*ft_new_left_str(char *left_str);

#endif
