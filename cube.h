/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:31:36 by bmartin           #+#    #+#             */
/*   Updated: 2023/05/04 17:09:58 by bmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE
# define CUBE

# include "../MLX42/include/GLFW/glfw3.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define IMG_PIXEL_SIZE 64

//message erreur
# define E_CHAR_INVALID "Error\n Found Invalid Character\n"
# define E_CHAR_MISSING "Error\n Mandatory Character Count Wrong\n"
# define E_MAP_TOO_WIDTH "Error\n Map Too Wide (Max 40)\n"
# define E_MAP_TOO_HEIGTH "Error\n Map Too High (max 21)\n"
# define E_MAP_LINE_DIFF "Error\n Lines Are Not Egal Length On Map\n"
# define E_MAP_BORDER "Error\n Map Border Missing\n"
# define E_FILE_NAME "Error\n File Name Is Invalid\n"
# define E_FLOODFILL "Error\n Floodfill Is Invalid\n"
# define E_ARGS_NUM "Error\n Argument Number is wrong\n"
# define E_FD_WRONG "Error:\n fd Error read value WRONG\n"

typedef struct s_data
{
	mlx_t			*mlx;
}					t_data;


//function

#endif
